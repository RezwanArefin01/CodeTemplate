const int N = 1e5 + 5;

vector<int> g[2 * N], gt[2 * N]; 
int n; // number of variables
int vis[2 * N], comp[2 * N], a[2 * N]; 
vector<int> ord; 

#define Not(x) ((x)^1)
#define var(x) (2 * (x))
#define zero(x) (2 * (x))
#define one(x) (2 * (x) + 1)

void addImp(int u, int v) {
  g[u].push_back(v); 
  gt[v].push_back(u); 
}

void forceTrue(int x) {
  addImp(Not(x), x); 
}

void addOr(int x, int y) {
  addImp(Not(x), y); 
  addImp(Not(y), x); 
}

void addXor(int x, int y) {
  addOr(x, y); 
  addOr(Not(x), Not(y)); 
}

void dfs(int u) {
  vis[u] = 1; 
  for(int v : g[u]) if(!vis[v]) dfs(v); 
  ord.push_back(u); 
}

void color(int u, int c) {
  comp[u] = c; 
  for(int v : gt[u]) if(!comp[v]) color(v, c); 
}

bool solve() {
  int V = 2 * n; 
  for(int i = 0; i < V; ++i) {
    if(!vis[i]) dfs(i); 
  }
  for(int i = 0, j = 0; i < V; ++i) {
    int v = ord[V - i - 1]; 
    if(!comp[v]) color(v, ++j); 
  }
  for(int i = 0; i < V; ++i) {
    if(comp[i] == comp[Not(i)]) return 0; 
    a[i] = comp[i] > comp[Not(i)]; 
  }
  // solution in a[var(i)]. 
  return 1;
}