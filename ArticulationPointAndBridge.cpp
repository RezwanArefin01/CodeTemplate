const int maxn = 1e5 + 10;
vector<int> adj[maxn];
int vis[maxn], low[maxn], cut[maxn], now = 0;

void dfs(int u, int par) {
	low[u] = vis[u] = ++now; int ch = 0; 
	for(int v : adj[u]) if(v - par) { 
		if(vis[v]) low[u] = min(low[u], vis[v]); 
		else { ch++;
			dfs(v, u); 
			low[u] = min(low[u], low[v]); 
			if(par + 1 && low[v] >= vis[u]) 
				cut[u] = 1;
			if(low[v] > vis[u]) {
				printf("Bridge %d -- %d\n", u, v);
			}
		}
	} if(par == -1 && ch > 1) cut[u] = 1;
}

void ArticulationPointAndBridge() {
	memset(vis, 0, sizeof vis);
	memset(low, 0, sizeof low); 
	memset(cut, 0, sizeof cut); 
	now = 0; 
	for(int i = 0; i < n; i++) {
		if(!vis[i]) dfs(i, -1); 
	}
}