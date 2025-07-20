#include <vector>

struct DSU {
    std::vector<int> size, parent;
    DSU(int n): size(n), parent(n, -1) {
        for (int i = 0; i < n; i++) make_set(i);
    }

    void make_set(int v) {
        parent[v] = v;
        size[v] = 1;
    }

    int find_set(int v) {
        if (parent[v] == v) return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_set(int v, int w) {
        v = find_set(v);
        w = find_set(w);
        if (v == w) return;

        if (size[w] > size[v]) std::swap(v, w);
        parent[w] = v;
        size[v] += size[w];
    }
};