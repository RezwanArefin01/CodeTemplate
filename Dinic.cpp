struct Dinic { // O(V^2 E)
  static const int N = 10000; 
  struct Edge { int v, cap, re; };
  int n, s, t, L[N]; 
  vector<Edge> E[N]; 

  void init(int _n, int _s, int _t) {
    n = _n, s = _s, t = _t; 
    for (int i = 0; i < n; ++i) E[i].clear(); 
  }
  void addEdge(int u, int v, int f) {
    E[u].push_back({v, f, (int)E[v].size()}); 
    E[v].push_back({u, 0, (int)E[u].size() - 1}); 
  }
  bool bfs() {
    for (int i = 0; i < n; ++i) L[i] = -1; 
    queue<int> q({s}); 
    L[s] = 0;
    while(!q.empty()) {
      int u = q.front(); q.pop(); 
      for (auto &it : E[u]) {
        if (it.cap > 0 && L[it.v] == -1) {
          L[it.v] = L[u] + 1; 
          q.push(it.v);
        }
      }
    }
    return L[t] != -1;
  }
  int dfs(int u, int pf) {
    if (u == t) return pf; 
    int ret = 0; 
    for (auto &it : E[u]) {
      if (it.cap > 0 && L[it.v] == L[u] + 1) {
        int tf = dfs(it.v, min(it.cap, pf));
        ret += tf; pf -= tf; it.cap -= tf; 
        E[it.v][it.re].cap += tf;
        if (pf == 0) return ret;
      }
    }
    if (!ret) L[u] = -1; 
    return ret; 
  }
  int flow(int ret = 0) {
    while(bfs()) ret += dfs(s, INT_MAX); 
    return ret; 
  }
};