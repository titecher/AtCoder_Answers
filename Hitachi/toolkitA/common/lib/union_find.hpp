#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <vector>

struct UnionFind{
    
		std::vector<int> M_par;
		std::vector<int> M_rank;
		std::vector<int> M_size;

private:
    void init(int n = 1){
        M_par.resize(n);
        M_rank.resize(n);
        M_size.resize(n);
        for(int i = 0; i < n; i++){
            M_par[i] = i;
            M_rank[i] = 0;
            M_size[i] = 1;
        }
    }

public:

    UnionFind(size_t n = 1){
        init(n);
    }

    size_t find(size_t x){
        if(M_par[x] == x) return x;
        size_t r = find(M_par[x]);
        return M_par[x] = r;
    }
    
    bool same(size_t x, size_t y){
        return find(x) == find(y);
    }

    bool unite(size_t x, size_t y){
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(M_rank[x] < M_rank[y]) std::swap(x, y);
        if(M_rank[x] == M_rank[y]) M_rank[x]++;
        M_par[y] = x;
        M_size[x] = M_size[x] + M_size[y];
        return true;
    }

    size_t size(size_t x){
        return M_size[find(x)];
    }

};

#endif
