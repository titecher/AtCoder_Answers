#ifndef RANDOM_GRAPH_GENERATOR_HPP
#define RANDOM_GRAPH_GENERATOR_HPP

#include <queue>
#include <tuple>
#include <cinttypes>
#include <utility>
#include <set>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm> 
#include "../utils/constraints.hpp"
#include "../lib/graph.hpp"
#include "../lib/random_number.hpp"
#include "../lib/union_find.hpp"
#include "./random_points_generator.hpp"
#include "./random_frequency_generator.hpp"

graph<edge> kruskal(std::vector<double> x, std::vector<double> y, std::vector<edge::cost_type> freq, random_number &rnd) {	
	
	// the number of vertices
	size_t N = x.size();
	graph<edge> G(N, freq);
	using Point = std::pair<size_t, size_t>;

	assert(MIN_N <= N and N <= MAX_N);
	
	// edges {cost, point}
	std::vector<std::pair<double, Point>> edges;
	
	// all to all distance
	std::vector<std::vector<double>> distance(N, std::vector<double> (N, 0.0));

	for(size_t u = 0; u < N; u++) {
		for(size_t v = u + 1; v < N; v++) {
			distance[u][v] = distance[v][u] = std::pow((x[u] - x[v]) * (x[u] - x[v]) + (y[u] - y[v]) * (y[u] - y[v]), 0.5);
			edges.push_back({distance[u][v], {u, v}});
		}
	}

	// sort edges
	std::sort(edges.begin(), edges.end());

	// manage connected components by using Union Find
	UnionFind uf(N);
	
	// create minimam spanninng tree
	for(size_t ei = 0; ei < edges.size(); ei++) {
		size_t u, v;
		std::tie(u, v) = edges[ei].second;
		double dis_u_v = edges[ei].first;
		
		if(uf.unite(u, v)) {
			edge::cost_type e_cost = ceil(dis_u_v * SCALE_ROAD);
			if(e_cost == 0) e_cost = 1;
			G.add_edge(u, v, e_cost);
			G.add_edge(v, u, e_cost);
		}
	}
	
	return G;
}

graph<edge> generate_random_graph(size_t N, size_t M, random_number &rnd) {
  assert(MIN_N <= N and N <= MAX_N);
  assert(N - 1 <= M and M <= N * (N - 1) / 2);
	
  size_t R = 1;
  for(size_t num = 1;; num++) {
    if(num * num > N) break;
    R = num;
  }	

  std::vector<double> x;
  std::vector<double> y;
  std::vector<size_t> degree(N, 0);
  std::tie(x, y) = random_points_generator(N, rnd);														// point
  std::vector<edge::cost_type> freq = random_frequency_generator(x, y, rnd);  // freqency
	std::vector<std::vector<double>> distance(N, std::vector<double> (N, 0.0)); // all to all distance
	using Point = std::pair<size_t, size_t>;

	for(size_t u = 0; u < N; u++) {
		for(size_t v = u + 1; v < N; v++) {
			distance[u][v] = distance[v][u] = std::pow((x[u] - x[v]) * (x[u] - x[v]) + (y[u] - y[v]) * (y[u] - y[v]), 0.5);
		}
	}
  
	// create minimam spanning tree
  graph<edge> G = kruskal(x, y, freq, rnd);
  
	// caluculate degree of certices
  for(size_t i = 0; i < N; i++) {
    for(auto e : G[i]) {
      size_t u, v, c;
      u = e.src;
      v = e.dst;
      if(u > v) continue;
      c = e.cost;
      degree[u]++;
      degree[v]++;
    }
  }

  // select edge greedy
  size_t restEdge = M - (N - 1);
  G.sort_edges();
	
	const double INF = 1e9;
	std::vector<std::vector<double>> edgeCost(N, std::vector<double> (N, INF));
	std::set<std::pair<double, Point>> edgeSet;

	// edgeCost[i][j] := distance[i][j] * deg[i] * deg[j] * f(u, v)
	// edgeSet := {edgeCost[i][j], {i, j}}

  for(size_t i = 0; i < N; i++) {
    for(size_t j = i + 1; j < N; j++) {
      if(G.find(i, j) != static_cast<size_t>(-1)) continue;
      double cost =  distance[i][j];
      assert(degree[i] != 0 and degree[j] != 0);
      cost = cost * degree[i] * degree[j];
      size_t x1 = i % R;
      size_t x2 = j % R;
      size_t y1 = i / R;
      size_t y2 = j / R;
		
			// if color(i) == color(j), cost 5 times
      if((x1 + x2 + y1 + y2) % 2 == 0) {
				cost *= 5;
      }

			edgeCost[i][j] = cost;		
			edgeSet.insert({cost, {i, j}});
    }
  }
	
  for(; restEdge > 0; restEdge--) {
		
		size_t u, v;
		// select the edge with the lowest cost
		std::pair<double, std::pair<size_t, size_t>> firstEdge = *edgeSet.begin();
		std::tie(u, v) = firstEdge.second;
		double cost = firstEdge.first;
		assert(cost == edgeCost[u][v]);
		if(cost == INF) break;
		edgeSet.erase({cost, {u, v}});
		edgeSet.insert({INF, {u, v}});
		edgeCost[u][v] = INF;
    assert(u < v);

    if(degree[u] < MAX_DEGREE and degree[v] < MAX_DEGREE) {
      degree[u]++;
      degree[v]++;
			
			// reculculate the cost of the edge adjacent to u, v
			for(size_t x = 0; x < N; x++) {
				
				if(x == u or x == v) continue;			

				// edge (u, x)
				{
					size_t a = std::min(u, x);
					size_t b = std::max(u, x);
					double curCost = edgeCost[a][b];
					if(curCost != INF) {
						assert(edgeSet.find({curCost, {a, b}}) != edgeSet.end());
						double nxtCost = curCost * degree[u] / (degree[u] - 1);
						edgeSet.erase({curCost, {a, b}});
						edgeSet.insert({nxtCost, {a, b}});
						edgeCost[a][b] = nxtCost;
					}
				}

				// edge (u, x)
				{
					size_t a = std::min(v, x);
					size_t b = std::max(v, x);
					double curCost = edgeCost[a][b];
					if(curCost != INF) {
					  assert(edgeSet.find({curCost, {a, b}}) != edgeSet.end());
						double nxtCost = curCost * degree[v] / (degree[v] - 1);
						edgeSet.erase({curCost, {a, b}});
						edgeSet.insert({nxtCost, {a, b}});
						edgeCost[a][b] = nxtCost;
					}
				}
			}		
	
	    edge::cost_type e_cost = ceil(distance[u][v] * SCALE_HIGHWAY);
     	if(e_cost == 0) e_cost = 1;
    	G.add_edge(u, v, e_cost);
    	G.add_edge(v, u, e_cost);
    }
  }
	
  return G;
}
#endif
