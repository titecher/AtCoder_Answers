#ifndef GRAPH_RELABELING_HPP
#define GRAPH_RELABELING_HPP

#include "../lib/graph.hpp"
#include "../lib/random_number.hpp"

graph<edge> graph_relabeling(const graph<edge> &g, random_number &rnd) {
  size_t N = g.size();
  graph<edge> r(N, std::vector<edge::cost_type>(N));

  std::vector<size_t> label(N);
  std::iota(label.begin(), label.end(), 0);
  rnd.shuffle(label.begin(), label.end());

  for(size_t i=0; i<N; i++) {
    for(auto edge : g[i]) {
      size_t src = label[edge.src], dst = label[edge.dst];
      edge::cost_type cost = edge.cost;
      r.add_edge(src, dst, cost);
    }
  }

  for(size_t i=0; i<N; i++) {
    r.f[ label[i] ] = g.f[i];
  }

  // depot
  r.f[0] = 0;
  r.sort_edges();
  return r;
}

#endif
