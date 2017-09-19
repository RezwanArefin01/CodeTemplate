 
const int maxn = 111;
struct Edmonds { // O(VE^2)
    struct edge { int u, v, cap, flow; };
    vector<edge> E; 
    vector<int> adj[maxn]; 
    int vis[maxn], par[maxn], Min[maxn]; 

    void clear() {
        E.clear();
        for(int i = 0; i < maxn; i++) 
            adj[i].clear();
    }
    
    void addEdge(int u, int v, int w) {
        E.push_back({u, v, w});
        adj[u].push_back(E.size() - 1);
        E.push_back({v, u, 0});
        adj[v].push_back(E.size() - 1);
    }
    int get(int s, int t) {
        int flow = 0;
        while(1) {
            memset(vis, 0, sizeof vis);
            memset(Min, 0, sizeof Min);
            queue<int> q; q.push(s); 
            Min[s] = 1e9, vis[s] = 1;
            while(!q.empty()) {
                int u = q.front(); q.pop();
                if(u == t) break; 
                for(int idx : adj[u]) {
                    edge e = E[idx]; int v = e.v;
                    if(!vis[v] && e.cap > e.flow) {
                        Min[v] = min(Min[u], e.cap - e.flow); 
                        par[v] = idx; 
                        q.push(v); 
                        vis[v] = 1;
                    }
                } 
            } if(Min[t] == 0) break;
            for(int u = t; u != s; u = E[par[u]].u) {
                E[par[u]].flow += Min[t]; 
                E[par[u] + 1].flow -= Min[t]; 
            } flow += Min[t];
        } return flow; 
    }
} mf; 