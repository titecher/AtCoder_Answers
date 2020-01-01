#ifndef RANDOM_POINTS_GENERATOR_HPP
#define RANDOM_POINTS_GENERATOR_HPP

#include <vector>
#include <utility>
#include "../utils/constraints.hpp"
#include "../lib/random_number.hpp"

std::pair<std::vector<double>, std::vector<double>> random_points_generator(size_t N, random_number &rnd) {
	assert(MIN_N <= N and N <= MAX_N);
	std::vector<double> x;
	std::vector<double> y;
	
	size_t M = 1;
	for(size_t num = 1;; num++) {
		if(num * num > N) break;
		M = num;
	}

	size_t restN = N - M * M;
	// N = M * M + rest_N;

	for(size_t i = 0; i < M; i++) {
		for(size_t j = 0; j < M; j++) {
			double dx = rnd.next_double();
			double dy = rnd.next_double();
			x.push_back(dx + i);
			y.push_back(dy + j);
		}
	}
	
	for(size_t i = 0; i < restN; i++) {
		x.push_back(rnd.next_double() * M);
		y.push_back(rnd.next_double() * M);
	}

	assert(N == x.size());
	assert(N == y.size());
	
	return make_pair(x, y);
}
#endif
