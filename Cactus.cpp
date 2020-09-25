// Vertex Cactus

const int N = 2e5 + 5;
vector<int> adj[N];
int n, m, l[N], r[N], vis[N], cycId[N], cyc; // cyc = n

stack<int> st;
void dfs(int u, int p) {
  vis[u] = 1;
  st.push(u);

  for (int i : adj[u]) {
    int v = u ^ l[i] ^ r[i];
    if (v == p) continue;
    if (vis[v]) {
      if (!cycId[v]) {
        cycId[v] = ++cyc;
        while (st.top() != v) {
          cycId[st.top()] = cyc;
          st.pop();
        }
        st.pop();
      }
    } else {
      dfs(v, u);
    }
  }

  if (!cycId[u]) cycId[u] = u;
  if(st.size() && st.top() == u) st.pop(); 
}
 
