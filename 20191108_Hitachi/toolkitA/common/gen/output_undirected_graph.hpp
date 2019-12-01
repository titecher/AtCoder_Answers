#ifndef OUTPUT_UNDIRECTED_GRAPH_HPP
#define OUTPUT_UNDIRECTED_GRAPH_HPP

#include "../lib/graph.hpp"
#include "../lib/random_number.hpp"
#include "../utils/constraints.hpp"

#include <cinttypes>
#include <vector>

void output_undirected_graph(const graph<edge> &G, random_number &rnd, FILE *fp) {
  size_t N = G.size();

  std::vector<edge> edges;
  for(size_t i=0; i<N; i++) {
    for(auto e : G[i]) {
      size_t u, v;
      u = e.src, v = e.dst;
      if(u > v) continue;
      edges.emplace_back(e);
    }
  }
  rnd.shuffle(edges.begin(), edges.end());

  size_t M = edges.size();
  fprintf(fp, "%zu %zu\n", N, M);
  for(auto e : edges) {
    size_t u, v; edge::cost_type c;
    u = e.src + INDEXED, v = e.dst + INDEXED, c = e.cost;
    if(rnd.next_int(0, 1)) std::swap(u, v);
    fprintf(fp, "%zu %zu %" PRId64 "\n", u, v, c);
  }
  
  fflush(fp);
}

#endif
