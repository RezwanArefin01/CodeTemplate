/*////////////////////////////////////////// 
p[u][i] = 2^i-th parent of u 
sub[u] = subtree size of tree rooted at u (including u)
chainHead[i] = head node of i-th chain 
chainNo[u] = number of chain where u belongs to 
otherend[i] = lower node of i-th edge; needed for edge query
base[] = base array for segment tree 
pos[u] = position of parent[u] - u edge's cost in base array
        in node update, p[u] = u's value in base array 
//////////////////////////////////////////*/

const int maxn = 10100;
int p[maxn][30], sub[maxn], n, L[maxn], lg;
vector<int> adj[maxn], cost[maxn], idx[maxn];

int chainHead[maxn], chainNo[maxn], otherend[maxn], 
    base[maxn], pos[maxn], ptr = 0, chain = 0; 


int tree[maxn<<2];
void build(int node, int l, int r) {
    if(l == r) {
        tree[node] = base[l]; 
        return;
    } int mid = l + r >> 1;
    build(node<<1, l, mid);
    build(node<<1|1, mid+1, r);
    tree[node] = max(tree[node<<1], tree[node<<1|1]);
}
void update(int node, int l, int r, int i, int val) {
    if(i > r || i < l) return;
    if(l == r) { 
        tree[node] = val;
        return;
    } int mid = l + r >> 1;
    update(node<<1, l, mid, i, val);
    update(node<<1|1, mid+1, r, i, val);
    tree[node] = max(tree[node<<1], tree[node<<1|1]);
}
int query(int node, int l, int r, int i, int j) {
    if(r < i || l > j) return -1;
    if(i <= l && r <= j) return tree[node];
    int mid = l + r >> 1;
    return max(query(node<<1, l, mid, i,j), 
                query(node<<1|1, mid+1, r, i,j));
}

void clean() {
    for(int i=0; i<=n; i++) {
        adj[i].clear();
        cost[i].clear();
        idx[i].clear();
    }
    memset(sub, 0, sizeof sub);
    memset(L, 0, sizeof L);
    memset(p, -1, sizeof p);
    memset(chainHead, -1, sizeof chainHead);
    lg = 0, ptr = 0, chain = 0;
    while((1<<lg) <= n) lg++;
}
void dfs(int u, int par) {
    p[u][0] = par;
    if(par+1) L[u] = L[par]+1;
    for(int i=1; i<=lg; i++) 
        if(p[u][i-1] + 1) 
            p[u][i] = p[p[u][i-1]][i-1];
    sub[u] = 1;
    for(int i=0; i<adj[u].size(); i++) {
        int v = adj[u][i]; 
        if(v == par) continue;
        otherend[idx[u][i]] = v;
        dfs(v, u);
        sub[u] += sub[v];
    }
}
int lca(int u, int v) {
    if(L[u] < L[v]) swap(u, v);
    for(int i=lg; i >=0; i--) 
        if(p[u][i] + 1 && L[p[u][i]] >= L[v]) 
            u = p[u][i];
    if(u == v) return u;
    for(int i=lg; i>=0; i--) 
        if(p[u][i] - p[v][i]) 
            v = p[v][i], u = p[u][i];
    return p[u][0];
}
void hld(int u, int par, int c) {
    if(chainHead[chain] == -1) 
        chainHead[chain] = u;
    chainNo[u] = chain;
    pos[u] = ptr;
    base[ptr++] = c;
    int Max = -1, sc = -1, ncost;
    for(int i=0; i<adj[u].size(); i++) {
        int v = adj[u][i], w = cost[u][i];
        if(v == par) continue; 
        if(sub[v] > Max) {
            Max = sub[v];
            sc = v, 
            ncost = w;
        }
    }
    if(sc+1) hld(sc, u, ncost);
    for(int i=0; i<adj[u].size(); i++) {
        int v = adj[u][i], w = cost[u][i];
        if(v == par || v == sc) continue; 
        chain++; 
        hld(v, u, w);
    }
}   
int queryup(int u, int v) {
    if(u == v) return 0;
    int uch, vch = chainNo[v], ret = 0;
    while(1) { 
        uch = chainNo[u];
        if(uch == vch) {
            if(u == v) break; 
            ret = max(ret, query(1, 0, ptr-1, pos[v]+1, pos[u])); // in nodes on path qurery 
                                                                // query(pos[v], pos[u])
            break;
        } ret = max(ret, query(1, 0, ptr-1, pos[chainHead[uch]], pos[u]));
        u = chainHead[uch];
        u = p[u][0];
    } return ret;
}
int query_hld(int u, int v) {
    int a = lca(u,v);
    return max(queryup(u, a), queryup(v, a));
}
void updateEdge(int i, int val) {
    update(1, 0, ptr-1, pos[otherend[i]], val);
}