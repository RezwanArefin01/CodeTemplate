struct dsu {
  vector<int> p;  // p[u] = u is root ? -size : parent;

  dsu(int n) : p(n + 1, -1) {}

  int Union(int u, int v) {
    u = Find(u), v = Find(v);
    if (u == v) return u;
    if (-p[u] < -p[v]) swap(u, v);
    p[u] += p[v];
    p[v] = u;
    return u;
  }

  int Find(int u) { return p[u] < 0 ? u : p[u] = Find(p[u]); }

  bool IsSame(int u, int v) { return Find(u) == Find(v); }

  int Size(int u) { return -p[Find(u)]; }
};
