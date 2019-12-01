#ifndef STATE_HPP
#define STATE_HPP

#include <cstdio>
#include <cassert>
#include <string>
#include <tuple>
#include <utility>
#include <iterator>
#include <functional>

class state : public agent {
public:
  using time_type = int_fast64_t;
  using query_type = int;
  using order_num_type = order::order_num_type;
  using score_type = int_fast64_t;
  
  static const std::string OK_STR;
  static const std::string NG_STR;
  const size_t depot_index;

  graph<edge> G;

  // 発生した注文をすべて記録 (id を 1-indexed にするために、先頭にダミー注文を入れる)
  std::vector<order> order_list;
  // グラフの、depot 以外の頂点それぞれについて未処理の注文を記録
  std::vector< std::set<order_num_type> > pending_order_list;
  // depot の頂点について、商品が agent に受け渡されていない注文を記録
  // agent について、その時点で保有している商品に対応する注文を記録
  std::set<order_num_type> depot_order_list, agent_order_list;
  time_type current_time, max_time;

  // コンテスタントのコマンド
  std::vector<int> commands;
  // 事前に与えられる注文の情報
  std::vector< std::vector<order> > given_order_info;
  
  state(const graph<edge> &G_, const time_type &max_time_,
	std::vector<int> commands_,
	std::vector< std::vector<order> > given_order_info_,
	size_t v);

  double prob_by_time();
  order_num_type next_dst();
  
  // コンテスタントから命令を受け取る・コマンドの判定結果を出す
  query_type input_by_agent();
  void output_verdict(std::string verdict);

  // 注文をランダムに追加する
  // (追加されたものは注文リストに追加し、コンテスタントに向けて出力)
  void get_order();

  // 現在地に応じて情報を更新
  // - agent が持つ商品が増える (depot にある商品が減る)
  // - agent が注文を処理し終える (各頂点にある未処理の注文が減り、終了時刻が記録される)
  void get_removed_order_list();
  void get_completed_order_list();
  
  // ステップ数を 1 進める
  // (コンテスタントから命令を受け取る・進める・状態更新・時間情報更新)
  // 不正な入力を受け取った時など、正常に終了しない時に false を返す
  bool increment_step();

  // スコア計算
  score_type calculate_score();

  // 注文の数の合計
  size_t get_num_of_orders() const;
  // 0-indexed で k 番目の注文情報を得る
  order get_kth_order(size_t k) const;
};

const std::string state::OK_STR = "OK";
const std::string state::NG_STR = "NG";

state::state(const graph<edge> &G_, const time_type &max_time_,
	     std::vector<int> commands_,
	     std::vector< std::vector<order> > given_order_info_,
	     size_t v=0)
  : agent(v), depot_index(v), G(G_),
    order_list(), pending_order_list(G_.size()),
    depot_order_list(), agent_order_list(),
    current_time(0), max_time(max_time_),
    commands(commands_), given_order_info(given_order_info_) {
  order_list.emplace_back(0, -1, -1); // ダミー注文
  G.sort_edges();
}

state::query_type state::input_by_agent() {
  return commands[current_time];
}

void state::output_verdict(std::string verdict) {
#ifdef DEBUG
  fprintf(stderr, "# verdict: %s\n", verdict.c_str());
#endif
}

void state::get_order() {
  using o_nt = order_num_type;

  std::vector<order> new_orders_list;
  for(size_t i=0; i<given_order_info[current_time].size(); i++) {
    const order &od = given_order_info[current_time][i];
    o_nt id, dst, start_time;
    std::tie(id, dst, start_time, std::ignore) = od.get_order_info();
    
    // 全体のリストに追加
    order_list.emplace_back(id, dst, start_time);

    // dst 番目の頂点に「待ち状態の注文」として情報を追加
    pending_order_list[dst].emplace(id);

    // depot に「持ち出し待ちの注文」として情報を追加
    depot_order_list.emplace(id);

    new_orders_list.emplace_back(id, dst, start_time);
  }
}

void state::get_removed_order_list() {
  using o_nt = order_num_type;
  size_t agent_v = ep_1;

  // depot から回収された商品に対応する注文一覧
  std::vector<o_nt> removed_order_list;
  if(agent_state == ON_VERTEX and agent_v == depot_index) {
    removed_order_list.reserve(depot_order_list.size());
    for(const auto &e : depot_order_list) {
      removed_order_list.emplace_back(e);
      agent_order_list.emplace(e);
    }
    depot_order_list.clear();
  }
}

void state::get_completed_order_list() {
  using o_nt = order_num_type;
  size_t agent_v = ep_1;

  // 処理された注文一覧
  std::vector<o_nt> completed_order_list;
  if(agent_state == ON_VERTEX and agent_v != depot_index) {
    set_intersection(pending_order_list[agent_v].begin(),
		     pending_order_list[agent_v].end(),
		     agent_order_list.begin(),
		     agent_order_list.end(),
		     std::back_inserter(completed_order_list));
    for(const auto &e : completed_order_list) {
      pending_order_list[agent_v].erase(e);
      agent_order_list.erase(e);
      // 終了時間を記録
      order_list[e].register_end_time(current_time);
    }
  }
}

bool state::increment_step() {
  const int V = static_cast<int>(G.size());

  // 新しく注文が来る
  // (注文リストを更新してコンテスタントに情報を送らないといけない)
  get_order();
  get_removed_order_list();
  
  // コンテスタントからの命令を受け取る
  query_type query = input_by_agent();

  // 命令を処理 (agent を動かすだけ！)
  if(query == -1) {
    // stay
    output_verdict(OK_STR);
  }
  else {
    int vertex = query - static_cast<int>(INDEXED);
    if(0 <= vertex and vertex < V) {
      // move
      if(is_valid_move(G, vertex)) {
	output_verdict(OK_STR);
	proceed(G, vertex);
      }
      else {
	output_verdict(NG_STR);
	return false;
      }
    }
    else {
      output_verdict(NG_STR);
      return false;
    }
  }

  // 命令を処理し終わったので 1 分経過させる
  current_time++;

  // その時点で捌いた注文のリスト・新しく持った商品のリストなどを得る
  get_completed_order_list();

  assert(pending_order_list[depot_index].empty());

  return true;
}

state::score_type state::calculate_score() {
  size_t num_of_orders = get_num_of_orders();

  auto func = [&](score_type s) {
    return s * s;
  };
  
  score_type score = 0;
  for(size_t i=0; i<num_of_orders; i++) {
    time_type start_time, end_time;
    std::tie(std::ignore, std::ignore, start_time, end_time) = get_kth_order(i).get_order_info();
    if(end_time != -1) {
      score += func(max_time) - func(end_time - start_time);
    }
  }
  return score;
}

size_t state::get_num_of_orders() const {
  return order_list.size() - 1;
}

order state::get_kth_order(size_t k) const {
  return order_list[k + 1];
}

#endif
