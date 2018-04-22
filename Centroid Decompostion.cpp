// Sample implementation of Centroid Decomposition.
// This solves the problem "count number of k length paths in tree"
// TODO: Do book-keeping in solve() instead of unordered_map

const int maxn = 1e5 + 10;
int n, k, vis[maxn], sub[maxn];
vector<int> adj[maxn]; 

void calc(int u, int par) { sub[u] = 1;  
	for(int v : adj[u]) if(!vis[v] && v - par) 
		calc(v, u), sub[u] += sub[v];
}
int centroid(int u, int par, int r) {
	for(int v : adj[u]) if(!vis[v] && v - par)
		if(sub[v] > r) return centroid(v, u, r);
	return u;
}

int dist[maxn]; ll ans;
int in[maxn], out[maxn], vert[maxn], tym = 0;

void dfs(int u, int par = -1, int d = 0) {
	dist[u] = d; 
	in[u] = tym; 
	vert[tym++] = u;
	for(int v : adj[u]) if(v - par && !vis[v]) 
		dfs(v, u, d + 1);
	out[u] = tym - 1;
}
void solve(int u) {
	tym = 0; dfs(u);
	unordered_map<int, int> cnt; cnt[0] = 1;
	for(int v : adj[u]) if(!vis[v]) {
		for(int t = in[v]; t <= out[v]; ++t) 
			if(dist[vert[t]] <= k)
				ans += cnt[k - dist[vert[t]]]; 
		for(int t = in[v]; t <= out[v]; ++t)
			++cnt[dist[vert[t]]];
	}
}
void decomp(int u, int par = -1) {
	calc(u, par);
	int c = centroid(u, par, sub[u] / 2); 
	solve(c); vis[c] = 1; 
	for(int v : adj[c]) if(!vis[v]) decomp(v, c);
}
