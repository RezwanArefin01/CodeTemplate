//BinaryLifting 
//LCA Routine 
//Dont 
const int maxn = 1e5+10;
const int MAXLOG = log2(maxn)+5;
vector<int> adj[maxn];
int p[maxn][MAXLOG], n, lg, L[maxn], timer = 0;
void dfs(int u, int par) {
	p[u][0] = par; 
	if(par + 1) 
		L[u] = L[par] + 1;
	for(int i=1; i<lg; i++)
		if(p[u][i-1] + 1)
			p[u][i] = p[p[u][i-1]][i-1];
	for(int v : adj[u]) if(par-v) dfs(v,u);
}
int get(int u, int v) {
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