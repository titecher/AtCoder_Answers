#include <set>
#include <vector>
#include <cinttypes>
#include <tuple>
#include <utility>
#include "../common/utils/constraints.hpp"
#include "../common/lib/graph.hpp"
#include "../common/lib/agent.hpp"
#include "../common/lib/order.hpp"
#include "../common/lib/state_for_problem_A.hpp"

int main(int argc, char **argv) {
  if(argc != 3) {
    fprintf(stderr, "Usage: %s <input-file> <output-file>\n", argv[0]);
    return 1;
  }
  FILE *inf = fopen(argv[1], "r");
  FILE *ouf = fopen(argv[2], "r");

  /* graph input */
  size_t V, E;
  fscanf(inf, "%zu%zu", &V, &E);

  graph<edge> G(V);
  for(size_t i=0; i<E; i++) {
    int u, v, dist;
    fscanf(inf, "%d%d%d", &u, &v, &dist);
    u -= INDEXED, v -= INDEXED;
    G.add_edge(u, v, dist);
    G.add_edge(v, u, dist);
  }

  /* T_{\max} input */
  int T_max; fscanf(inf, "%d", &T_max);

  /* given order input */
  std::vector< std::vector<order> > given_order_info(T_max);
  for(int i=0; i<T_max; i++) {
		int N;
    fscanf(inf, "%d", &N);
    for(int j=0; j<N; j++) {
			int new_id, dst;
			fscanf(inf, "%d %d", &new_id, &dst);
      dst -= INDEXED;
      given_order_info[i].emplace_back(new_id, dst, i);
    }
  }

  /* command output (contestant) */
  std::vector<int> commands(T_max);
  for(int i=0; i<T_max; i++) {
		fscanf(ouf, "%d", &commands[i]);
    assert(commands[i] != 0);
  }

  state st(G, T_max, commands, given_order_info);
  for(int i=0; i<T_max; i++) {
    assert(st.increment_step());
  }

  printf("SCORE = %" PRId64 "\n", st.calculate_score());
  return 0;
}
