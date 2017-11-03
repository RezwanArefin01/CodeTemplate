/*////////////////////////////////////////// 
p[u] = parent of u; 
head[u] = chain head of u in its chain
pos[u] = position of u in segment tree.
//////////////////////////////////////////*/

vector<int> adj[maxn]; 
int n, p[maxn], heavy[maxn], dep[maxn], head[maxn], pos[maxn];
int dfs(int u, int par) {
    if(par + 1) dep[u] = dep[par] + 1; 
    int size = 1, Max = 0; p[u] = par; 
    for(int v : adj[u]) if(v - par) {
        int sub = dfs(v, u);
        if(sub > Max) Max = sub, heavy[u] = v; 
        size += sub; 
    } return size;
}
template <class BinaryOperation>
void processPath(int u, int v, BinaryOperation op) {
    for(; head[u] != head[v]; u = p[head[u]]) {
        if(dep[head[v]] > dep[head[u]]) swap(u, v);
        op(pos[head[u]], pos[u]);
    } if(dep[v] > dep[u]) swap(u, v);
    op(pos[v], pos[u]);
}
int updatePath(int u, int v, int val) {
    processPath(u, v, [&val](int l, int r) { tree.update(l, r, v); });
}
int queryPath(int u, int v) {
    int ret = 0;
    processPath(u, v, [&ret](int l, int r) { ret += tree.query(l, r); });
    return ret;
}
void init() {
    fill_n(heavy, n, -1); dfs(0, -1);
    for(int i = 0, idx = 0; i < n; i++) {
        if(p[i] == -1 || heavy[p[i]] != i) {
            for(int j = i; j + 1; j = heavy[j]) {
                head[j] = i; 
                pos[j] = idx++;
            }
        }
    } tree.init(n);
    for(int i = 0; i < n; i++) 
        tree.set(pos[i], value[i]);
}