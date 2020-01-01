#ifndef OUTPUT_FREQUENCY_HPP
#define OUTPUT_FREQUENCY_HPP

#include "../lib/graph.hpp"
#include "../lib/random_number.hpp"
#include "../utils/constraints.hpp"

#include <cinttypes>
#include <vector>

void output_frequency(const graph<edge> &G, FILE *fp) {
  size_t N = G.size();
  for(size_t i = 0; i < N; i++) {
    size_t f = G.f[i];
    if(i + 1 == N) fprintf(fp, "%zu\n", f);
    else           fprintf(fp, "%zu ",  f);
  }

  fflush(fp);
}

#endif
