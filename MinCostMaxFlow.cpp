template <int N, class T = int>
class MCMF {
 public:
  struct Edge {
    int u, v;
    T cap, cost, flow;
    Edge(int u, int v, T cap, T cost, T flow)
        : u(u), v(v), cap(cap), cost(cost), flow(flow) {}
  };
  const T inf = numeric_limits<T>::max();
  vector<int> adj[N];
  vector<Edge> E;
  bitset<N> vis;
  queue<int> q;
  int n, s, t, ptr[N];
  T dist[N], total_cost;

  inline void init(int _n, int _s, int _t) {
    n = _n, s = _s, t = _t;
    total_cost = 0, E.clear();
    for (int i = 0; i < n; ++i) adj[i].clear();
  }
  inline void addEdge(int u, int v, T cap, T cost, bool directed = true) {
    adj[u].push_back(E.size());
    E.emplace_back(u, v, cap, cost, 0);
    adj[v].push_back(E.size());
    E.emplace_back(v, u, 0, -cost, 0);
    if (!directed) addEdge(v, u, cap, cost, true);
  }
  inline bool spfa() {
    fill(dist, dist + n, inf);
    q.push(s), dist[s] = 0, vis[s] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop(), vis[u] = 0;
      for (int i : adj[u]) {
        if (E[i].flow < E[i].cap && dist[E[i].v] > dist[u] + E[i].cost) {
          dist[E[i].v] = dist[u] + E[i].cost;
          if (!vis[E[i].v]) q.push(E[i].v), vis[E[i].v] = 1;
        }
      }
    }
    return dist[t] != inf;
  }
  T dfs(int u, T pf) {
    if (u == t || !pf) return pf;
    vis[u] = 1;
    while (ptr[u] < adj[u].size()) {
      int i = adj[u][ptr[u]];
      if (!vis[E[i].v] && dist[E[i].v] == dist[u] + E[i].cost) {
        if (T x = dfs(E[i].v, min(pf, E[i].cap - E[i].flow))) {
          total_cost += x * E[i].cost;
          E[i].flow += x, E[i ^ 1].flow -= x;
          vis[u] = 0;
          return x;
        }
      }
      ++ptr[u];
    }
    return vis[u] = 0;
  }
  pair<T, T> flow() {
    T mf = 0;
    while (spfa()) {
      memset(ptr, 0, n * sizeof(ptr[0]));
      while (T f = dfs(s, inf)) mf += f;
    }
    return {mf, total_cost};
  }
};
