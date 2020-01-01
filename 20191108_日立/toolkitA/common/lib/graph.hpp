#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <cstdint>
#include <cstddef>
#include <algorithm>

class edge {
public:
  using cost_type = int_fast64_t;
  static const cost_type INF = 1LL << 28;
  
  size_t src, dst;
  cost_type cost;
  
  edge() : cost(INF) {}
  edge(size_t u, size_t v, cost_type c) : src(u), dst(v), cost(c) {}
};

const edge::cost_type INF = 1 << 28;

template <typename edge_type>
class graph {
public:
  using cost_type = typename edge_type::cost_type;
  std::vector< std::vector<edge_type> > g;
  std::vector<cost_type> f; // frequency

  graph() = default;
  graph(size_t N) : g(N), f(N) {}
  graph(size_t N, const std::vector<cost_type> freq) : g(N), f(freq) { sort_edges(); }
  graph(const graph &g_) : g(g_.g), f(g_.f) { sort_edges(); }
  size_t size() const { return g.size(); }
  const std::vector<edge_type>& operator[](int k) const { return g[k]; }
  std::vector<edge_type>& operator[](int k) { return g[k]; }

  void add_edge(size_t u, size_t v, size_t c) {
    g[u].emplace_back(u, v, c);
  }

  void sort_edges() {
    for(size_t i=0; i<g.size(); i++) {
      std::sort(g[i].begin(), g[i].end(), [](edge_type a, edge_type b) {
	  return a.dst < b.dst;
	});
    }
  }

  // 頂点 u と直接結ばれている辺であって、端点が v であるもの (のインデックス) を返す
  size_t find(size_t u, size_t v) const {
    size_t lb = 0, ub = g[u].size();
    while(ub - lb > 1) {
      size_t mid = (ub + lb) >> 1;
      if(g[u][mid].dst <= v) lb = mid;
      else ub = mid;
    }

    if(g[u][lb].dst == v) return lb;
    else return -1;
  }
};

#endif
