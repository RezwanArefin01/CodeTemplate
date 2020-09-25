const int maxn = 2*5e4+10; 
const int inf = 1e9; 

vector<int> adj[maxn]; 
int match[maxn], dist[maxn], n, m, p;

bool bfs() {
    queue<int> Q; 
    for(int i = 1; i <= n; i++) {
        if(!match[i]) dist[i] = 0, Q.push(i);
        else dist[i] = inf;
    } dist[0] = inf;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        if(u == 0) continue; 
        for(int v : adj[u]) {
            if(dist[match[v]] == inf) {
                dist[match[v]] = dist[u] + 1, 
                Q.push(match[v]);
            }
        }
    } return dist[0] != inf;    
}

bool dfs(int u) {
    if(!u) return 1; 
    for(int v : adj[u]) {
        if(dist[match[v]] == dist[u] + 1) {
            if(dfs(match[v])) {
                match[u] = v, match[v] = u;
                return 1; 
            }
        } 
    } dist[u] = inf; return 0;
}

int hopcroft_karp() {
    int ret = 0; 
    while(bfs()) 
        for(int i = 1; i <= n; i++) 
            if(!match[i] && dfs(i)) 
                ret++;
    return ret;
} 
