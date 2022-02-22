template <int N, class T = int>
class MaxFlow {
 public:
  struct Edge {
    int u, v;
    T cap, flow;
    Edge(int u, int v, T cap, T flow) : u(u), v(v), cap(cap), flow(flow) {}
  };
  vector<int> adj[N];
  vector<Edge> E;
  int n, s, t, ptr[N], dist[N], Q[N];

  inline void init(int _n, int _s, int _t) {
    n = _n, s = _s, t = _t;
    E.clear();
    for (int i = 0; i < n; ++i) {
      adj[i].clear();
    }
  }
  inline void addEdge(int u, int v, T cap, bool directed = true) {
    adj[u].push_back(E.size());
    E.emplace_back(u, v, cap, 0);
    adj[v].push_back(E.size());
    E.emplace_back(v, u, directed ? 0 : cap, 0);
  }
  inline bool bfs() {
    memset(dist, -1, sizeof(dist[0]) * n);
    int f = 0, l = 0;
    dist[s] = 0, Q[l++] = s;
    while (f < l && dist[t] == -1) {
      int u = Q[f++];
      for (int i : adj[u]) {
        if (dist[E[i].v] == -1 && E[i].flow < E[i].cap)
          Q[l++] = E[i].v, dist[E[i].v] = dist[u] + 1;
      }
    }
    return dist[t] != -1;
  }
  T dfs(int u, T pf) {
    if (u == t || !pf) return pf;
    while (ptr[u] < adj[u].size()) {
      int i = adj[u][ptr[u]];
      if (dist[E[i].v] == dist[u] + 1) {
        if (T x = dfs(E[i].v, min(pf, E[i].cap - E[i].flow))) {
          E[i].flow += x, E[i ^ 1].flow -= x;
          return x;
        }
      }
      ++ptr[u];
    }
    return 0;
  }
  T flow() {
    T res = 0;
    while (bfs()) {
      memset(ptr, 0, n * sizeof(ptr[0]));
      while (T f = dfs(s, numeric_limits<T>::max())) res += f;
    }
    return res;
  }
};

