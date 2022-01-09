const int N = 1e5 + 5;
const int inf = 1e9;
vector<int> adj[N];
int match[N], dist[N], n, m, p;

bool bfs() {
  queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (!match[i])
      dist[i] = 0, q.push(i);
    else
      dist[i] = inf;
  }
  dist[0] = inf; 
  while(!q.empty()) {
    int u = q.front(); 
    q.pop(); 
    if(!u) continue; 
    for(int v : adj[u]) {
      if(dist[match[v]] == inf) {
        dist[match[v]] = dist[u] + 1; 
        q.push(match[v]); 
      }
    }
  }
  return dist[0] != inf;
}

bool dfs(int u) {
  if(!u) return 1; 
  for(int v : adj[u]) {
    if(dist[match[v]] == dist[u] + 1) {
      if(dfs(match[v])) {
        match[u] = v, match[v] = u; 
        return 1; 
      }
    }
  }
  dist[u] = inf; 
  return 0; 
}

int max_matching() {
  int ret = 0;
  while (bfs()) {
    for (int i = 1; i <= n; ++i)
      if (!match[i] && dfs(i)) ++ret;
  }
  return ret;
}
