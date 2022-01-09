typedef pair<ll, ll> ii;
struct CostFlow {
  static const int N = 105;
  static const ll inf = 1e18;

  struct Edge {
    int v, r;
    ll f, c;
  };

  int n, s, t, prv[N], prvL[N], inq[N];
  ll d[N], fl, cost;
  vector<Edge> E[N];

  void init(int _n, int _s, int _t) {
    n = _n, s = _s, t = _t;
    for (int i = 0; i < n; ++i) E[i].clear();
    fl = cost = 0;
  }

  void addEdge(int u, int v, ll f, ll c) {
    E[u].push_back({v, (int)E[v].size(), f, c});
    E[v].push_back({u, (int)E[u].size() - 1, 0, -c});
  }

  ii flow() {
    while (true) {
      for (int i = 0; i < n; ++i) d[i] = inf, inq[i] = 0;
      d[s] = 0;
      queue<int> q({s});
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (int i = 0; i < E[u].size(); ++i) {
          int v = E[u][i].v;
          ll w = E[u][i].c;
          if (E[u][i].f > 0 && d[v] > d[u] + w) {
            prv[v] = u, prvL[v] = i;
            d[v] = d[u] + w;
            if (!inq[v]) inq[v] = 1, q.push(v);
          }
        }
      }
      if (d[t] == inf) break;
      ll tf = inf;
      for (int v = t, u, l; v != s; v = u) {
        u = prv[v], l = prvL[v];
        tf = min(tf, E[u][l].f);
      }
      for (int v = t, u, l; v != s; v = u) {
        u = prv[v], l = prvL[v];
        E[u][l].f -= tf;
        E[v][E[u][l].r].f += tf;
      }
      cost += tf * d[t];
      fl += tf;
    }
    return {fl, cost};
  }
};