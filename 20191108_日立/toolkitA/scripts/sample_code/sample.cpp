#include <iostream>
#include <vector>
#include <utility>

int main() {
		
	// recieve |V| and |E|
	int V, E; std::cin >> V >> E;
	std::vector<std::vector<std::pair<int, int>>> G(V);
	
	for(int i = 0; i < E; i++) {
		// recieve edges
		int u, v, d; std::cin >> u >> v >> d;
		u--; v--;
		G[u].push_back({v, d});
		G[v].push_back({u, d});
	}
	
	int Tmax; std::cin >> Tmax;

	// recieve info
	for(int i = 0; i < Tmax; i++) {
		int Nnew; std::cin >> Nnew;
		for(int j = 0; j < Nnew; j++) {
			int new_id, dst; std::cin >> new_id >> dst;
		}
	}

  // insert your code here to get more meaningful output
	// all stay
	for(int i = 0; i < Tmax; i++) std::cout << -1 << std::endl;
	return 0;
}
