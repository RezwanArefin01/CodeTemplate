/*////////////////////
adj[] is the main graph
trans[] strores tranpose graph
col[u] will store the component number where u belongs to
////////////////////*/
const int maxn = 1e5 + 10; 
vector<int> adj[maxn], trans[maxn]; 
int col[maxn], vis[maxn], idx = 0, n, m; 
stack<int> st; 

void dfs(int u) {
	vis[u] = 1;
	for(int v : adj[u]) if(!vis[v]) dfs(v);
	st.push(u);
}
void dfs2(int u) {
	col[u] = idx;
	for(int v : trans[u]) if(!col[v]) dfs2(v);
}
void scc() {
	for(int i = 1; i <= n; i++) 
		if(!vis[i]) dfs(i);

	for(int u = 1; u <= n; u++)
		for(int v : adj[u]) 
			trans[v].push_back(u);

	while(!st.empty()) {
		int u = st.top(); st.pop();
		if(col[u]) continue; 
		idx++; dfs2(u); 
	} 
}