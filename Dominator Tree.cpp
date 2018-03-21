/* ///////////////////////
 * adj[u] contains child of u in dominator tree 
 * par[u] contains parent of u in DAG
 * dom[u] = immediate dominator of u
*/////////////////////////
vector<int> adj[maxn], par[maxn], topo; 
int dom[maxn], L[maxn], p[maxn][22], vis[maxn];

void addEdge(int u, int v) { // Construct your DAG using this fucntion. 
	adj[u].push_back(v);
	par[v].push_back(u);
}
void dfs(int u) { // topo sort 
	if(vis[u]) return; vis[u] = 1;
	for(int v : adj[u]) if(!vis[v]) dfs(v);
	topo.push_back(u);
}
void addToTree(int par, int u) { // Adds edge (par, u) to dominator tree. 
	dom[u] = par; p[u][0] = par; 
	L[u] = L[par] + 1; 
	for(int i = 1; i <= 20; ++i) 
		if(p[u][i - 1] + 1) 
			p[u][i] = p[p[u][i-1]][i-1];
}
int lca(int u, int v) { 
	if(L[u] < L[v]) swap(u, v);
	for(int i = 20; i >= 0; --i) 
		if(p[u][i] + 1 && L[p[u][i]] >= L[v]) 
			u = p[u][i]; 
	if(u == v) return u; 
	for(int i = 20; i >= 0; --i) 
		if(p[u][i] - p[v][i]) 
			u = p[u][i], v = p[v][i]; 
	return p[v][0]; 
}
void DominatorTree(int root) {
	dfs(root); 
	memset(p, -1, sizeof p); 
	memset(dom, -1, sizeof dom);
	for(int i = (int) topo.size() - 2; i >= 0; --i) {
		int u = topo[i], d = -1;  
		for(int v : par[u]) d = d == -1 ? v : lca(v, d); 
		addToTree(d, u); 
	} 
} 
