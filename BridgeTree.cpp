const int N = 2e5 + 5;
vector<int> adj[N];
int n, m, vis[N], low[N], tym, idx;
stack<int> st;
vector<vector<int>> comps;

void generate_comp(int v = -1) {
  vector<int> comp;
  while (st.size()) {
    int w = st.top();
    comp.push_back(w); 
    // comp[w] = idx; 
    st.pop();
    if(w == v) break; 
  }
  comps.push_back(comp);
}

void dfs(int u, int p) {
  low[u] = vis[u] = ++tym;
  st.push(u);
  for (int v : adj[u]) {
    if (vis[v]) {
      if (v != p) low[u] = min(low[u], vis[v]);
      else p = 0;
    } else {
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > vis[u]) generate_comp(v);
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);
  while (m--) {
    int u, v;
    scanf("%d %d", &u, &v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  for (int i = 1; i <= n; ++i) {
    if (vis[i]) continue;
    dfs(i, 0);
    // roots.push_back(idx);
    generate_comp(); 
  }

  return 0;
}