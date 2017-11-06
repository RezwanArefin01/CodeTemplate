const int inf = 1e9; // larger than Min Cut
const int maxn = 160;

int cost[maxn][maxn], w[maxn];
bool vis[maxn], merged[maxn]; 
vector<int> bestCut;

int MinCut(int n) {
	int best = inf; merged[0] = 1;
	for(int i = 1; i < n; i++) merged[i] = 0;
	// vector<int> cut; 
	for(int phase = 1; phase < n; ++phase) {
		vis[0] = 1; 
		for(int i = 1; i < n; ++i) if(!merged[i]) 
			vis[i] = 0, w[i] = cost[0][i];
		
		int prv = 0, nxt; 
		for(int i = n - 1 - phase; i >= 0; --i) {
			nxt = -1; 
			for(int j = 1; j < n; ++j) 
				if(!vis[j] && (nxt == -1 || w[j] > w[nxt])) 
					nxt = j;
			vis[nxt] = 1; 
			if(i) { prv = nxt;
				for(int j = 1; j < n; ++j) 
					if(!vis[j]) w[j] += cost[nxt][j];
			}
		} 
		for(int i = 0; i < n; i++) 
			cost[i][prv] = (cost[prv][i] += cost[nxt][i]);
		merged[nxt] = 1;
		// cut.push_back(nxt); 
		if(best > w[nxt]) {
			best = w[nxt];
			// bestCut = cut;
		}
	} return best;
}