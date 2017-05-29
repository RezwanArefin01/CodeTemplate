const int maxn = 1e5 + 10;
set<int> adj[maxn];
int p[maxn][32], lg, L[maxn];
//LCA Routine
//Don't Forget to memset p array ;) 
void lcadfs(int u, int par) {
	p[u][0] = par; 
	if(par + 1) 
		L[u] = L[par] + 1;
	for(int i=1; i<lg; i++)
		if(p[u][i-1] + 1) 
			p[u][i] = p[p[u][i-1]][i-1];
	for(int v : adj[u]) if(par-v) lcadfs(v,u);
}
int lca(int u, int v) {
	if(L[u] < L[v]) swap(u,v);
	for(int i=lg; i>=0; i--) 
		if(p[u][i] + 1 && L[p[u][i]] >= L[v])
			u = p[u][i];
	if(v == u) return u;
	for(int i=lg; i>=0; i--) 
		if(p[u][i] - p[v][i])
			v = p[v][i], u = p[u][i];
	return p[v][0];
}

int dist(int u, int v) {
	return L[u] + L[v] - 2*L[lca(u,v)];
}

//centroid Decomposition
int parent[maxn], sub[maxn];  //parent[u] = parent of u in Centroid Tree
void addEdge(int u, int v) {
	adj[u].insert(v);
	adj[v].insert(u);
}
void dfs(int u, int par) {
	sub[u] = 1;
	for(int v : adj[u]) if(par-v) {
		dfs(v,u); sub[u] += sub[v];
	}
}
int centroid(int u, int par, int sz) {
	for(int v : adj[u]) if(par-v) 
		if(sub[v] > sz) 
			return centroid(v, u, sz);
	return u;
}

void decompose(int u, int par) {
	dfs(u, -1); 
	int c = centroid(u, -1, sub[u]/2);
	parent[c] = par; 
	for(int v : adj[c]) {
		adj[v].erase(c);
		decompose(v, c);
	} adj[c].clear();
}