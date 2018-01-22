const int maxn = 1e5 + 10;
vector<int> adj[maxn]; 
int p[maxn][18], L[maxn]; 
int ans[maxn], vis[maxn], sub[maxn], par[maxn];

void dfs(int u, int par) {
	if(par + 1) L[u] = L[par] + 1;
	p[u][0] = par;
	for(int i = 1; i <= 17; ++i) 
		if(p[u][i-1] + 1) 
			p[u][i] = p[p[u][i-1]][i-1];
	for(int v : adj[u]) if(v - par) dfs(v, u);
}
int lca(int u, int v) {
	if(L[u] < L[v]) swap(u, v);
	for(int i = 17; i >= 0; --i) 
		if(p[u][i] + 1 && L[p[u][i]] >= L[v]) 
			u = p[u][i];
	if(u == v) return u; 
	for(int i = 17; i >= 0; --i) 
		if(p[u][i] - p[v][i]) 
			u = p[u][i], v = p[v][i];
	return p[u][0];
}

int dist(int u, int v) { return L[u] + L[v] - (L[lca(u, v)] << 1); }

void calc(int u, int par) { sub[u] = 1; 
	for(int v : adj[u]) if(!vis[v] && v - par) 
		calc(v, u), sub[u] += sub[v];
}
int centroid(int u, int par, int r) {
	for(int v : adj[u]) if(!vis[v] && v - par) 
		if(sub[v] > r) return centroid(v, u, r);
	return u;
}
void decompose(int u, int f) {
	calc(u, f);
	int c = centroid(u, -1, sub[u] >> 1);
	vis[c] = 1;	par[c] = f;
	for(int v : adj[c]) if(!vis[v]) decompose(v, c);
}

void update(int u) {
	for(int v = u; v + 1; v = par[v]) 
		ans[v] = min(ans[v], dist(u, v));
}
int query(int u) {
	int ret = 1e9;
	for(int v = u; v + 1; v = par[v])
		ret = min(ret, ans[v] + dist(u, v));
	return ret;
}