// Complexity $O(V * min(BPM^2, E))$.
// Left nodes - 0, 1, ..., n - 1. Right rest.  
vector<int> adj[N]; 
int vis[N], match[N], iter; 
int dfs(int u) {
    if(vis[u] == iter) return 0;
    vis[u] = iter; 
    for(int v : adj[u]) {
        if(match[v] < 0 || dfs(match[v])) {
            match[u] = v, match[v] = u;
            return 1; 
        }
    } return 0; 
}
int kuhn() {
    memset(match, -1, sizeof match); 
    int ans = 0; 
    for(int i = 0; i < n; i++) {
        ++iter; ans += dfs(i); 
    } return ans; 
}