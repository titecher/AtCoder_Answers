#include "../common/utils/constraints.hpp"
#include "../common/lib/graph.hpp"
#include "../common/lib/random_number.hpp"
#include "../common/gen/random_graph_generator.hpp"
#include "../common/gen/graph_relabeling.hpp"
#include "../common/gen/output_undirected_graph.hpp"
#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>

int main (int argc, char **argv) {
	
	if(argc != 4) {
		fprintf(stderr, "Usage: %s <filename> <case-type> <seed>\n", argv[0]);
		return 1;
	}
	
	int case_type = (int)std::stoull(argv[2]) - 1;
	if(case_type < 0 or case_type > NUM_OF_CASE) {
		fprintf(stderr, "Error: case-type is invalid\n");
		fprintf(stderr, "   random-case => 1\n");
		fprintf(stderr, "   max-case => 2\n");
	}
	
	uint_fast64_t seed = std::stoull(argv[3]);

	random_number rnd(seed);
	FILE *fp = fopen(argv[1], "w");
	if(fp == NULL) {
		fprintf(stderr, "Error: cannot open the file\n");
	}

	size_t N, M;
	if(case_type == 0) {
		N = rnd.next_uint(MIN_N, MAX_N);
	} else {
		N = MAX_N;
	}
	
	M = rnd.next_uint((N * 3 + 2 - 1) / 2, N * 2);
	graph<edge> G = generate_random_graph(N, M, rnd);
	G = graph_relabeling(G, rnd);
	output_undirected_graph(G, rnd, fp);
	
	double time_peak = rnd.next_double() * 0.95;
  std::vector<std::pair<double, double>> prob_segment;
	prob_segment.emplace_back(0.0, 0.0);
	prob_segment.emplace_back(time_peak, 1);
	prob_segment.emplace_back(0.95, 0.0);
	prob_segment.emplace_back(1.1, 0.0);
	
	
	fprintf(fp, "%zu\n", TIME_LIMIT);
  int current_time = 0;
  int new_id = 1;
		
  std::vector<size_t> freq_pool;
  for(size_t i=0; i<G.size(); i++) {
		for(int j=0; j<static_cast<int>(G.f[i]); j++) {
	  	freq_pool.emplace_back(i);
		}
  }

  assert(prob_segment.size() > 0);
  auto prob_by_time = [&] {
		double t = 1.0 * current_time / TIME_LIMIT;
  
		if(prob_segment.size() == 1) {
	  	return prob_segment.front().second;
		} 
		else {
	  	for(size_t i = 0; i + 1 < prob_segment.size(); i++) {
	    	double t1 = prob_segment[i].first, t2 = prob_segment[i+1].first;
		    double p1 = prob_segment[i].second, p2 = prob_segment[i+1].second;
				
		    if(t1 <= t and t <= t2) {
	  	    double delta_p = p2 - p1;
	    	  double ratio = (t - t1) / (t2 - t1);
	      	return p1 + ratio * delta_p;
		    }
		  }
	  	assert(false);
	  	return -1.0;
		}
  };

  for(; current_time < TIME_LIMIT; current_time++) {
		double prob = prob_by_time();
		if(rnd.next_double() <= prob) {
			size_t idx = rnd.next_uint(0, freq_pool.size() - 1);
			fprintf(fp, "1\n");
			fprintf(fp, "%d %zu\n", new_id, freq_pool[idx] + 1);
			new_id++;
		} else {
			fprintf(fp, "0\n");
		}
  }
	
	return 0;
}
