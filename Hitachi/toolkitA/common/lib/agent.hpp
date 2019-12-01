#ifndef AGENT_HPP
#define AGENT_HPP

#include <cassert>

class agent {
public:
  enum AGENT_STATE {
    ON_EDGE = 1,
    ON_VERTEX = 2,
  };

protected:
  // ON_EDGE: u と v を結ぶ辺上にいて、u から d 離れた地点にいる
  // ON_VERTEX: u 上にいる
  AGENT_STATE agent_state;
  size_t ep_1, ep_2;
  edge::cost_type agent_pos, edge_length;

public:
  // 店 は 0 番目の頂点
  agent() = default;
  agent(size_t v) : agent_state(ON_VERTEX),
		    ep_1(v), ep_2(-1),
		    agent_pos(0), edge_length(-1) {}

  void change_agent_state(size_t x) {
    agent_state = ON_VERTEX;
    ep_1 = x, ep_2 = -1;
    agent_pos = 0, edge_length = -1;
  }
  void change_agent_state(size_t x, size_t y,
			  edge::cost_type c, edge::cost_type d) {
    assert(abs(c - agent_pos) == 1);

    agent_state = ON_EDGE;
    ep_1 = x, ep_2 = y;
    agent_pos = c, edge_length = d;

    // agent_pos が 0 の場合は x に到達している
    if(agent_pos == 0) {
      change_agent_state(x);
      return;
    }

    // agent_pos が d の場合は y に到達している
    if(agent_pos == d) {
      change_agent_state(y);
      return;
    }
  }

  // 現在地から v に向けて進むことが valid であるか
  template <typename graph_type>
  bool is_valid_move(const graph_type &g, size_t v) {
    if(agent_state == ON_EDGE) {
      if(ep_1 == v and
	 0 <= agent_pos - 1 and agent_pos - 1 <= edge_length)
	return true;
      if(ep_2 == v and
	 0 <= agent_pos + 1 and agent_pos + 1 <= edge_length)
	return true;
    
      return false;
    }
    else if(agent_state == ON_VERTEX) {
      return g.find(ep_1, v) != size_t(-1);
    }
    else assert(false);
  }

  // 現在地から v に向けて 1 進める (agent の情報を更新)
  // あくまで移動させるだけであり、その他の情報更新は別
  // (辺の長さが 1 の時がやばいと思うので注意)
  template <typename graph_type>
  void proceed(const graph_type &g, size_t v) {
    assert(is_valid_move(g, v));
    
    // 辺上にあるときの移動
    if(agent_state == ON_EDGE) {
      if(ep_1 == v) {
	change_agent_state(ep_1, ep_2, agent_pos - 1, edge_length);
      }
      if(ep_2 == v) {
	change_agent_state(ep_1, ep_2, agent_pos + 1, edge_length);
      }
    }
    // 頂点上にあるときの移動
    else if(agent_state == ON_VERTEX) {
      size_t edge_idx = g.find(ep_1, v);
      edge::cost_type len = g[ep_1][edge_idx].cost;
      change_agent_state(ep_1, v, 1, len);
    }
  }
};

#endif
