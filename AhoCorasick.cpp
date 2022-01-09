soconst int N = 1e6 + 10;
int trie[N][26], link[N], idx, tot[N]; 
char p[N], s[N]; 

void insert() {
	int u = 0, len = strlen(p);
	for(int i = 0; i < len; i++) {
		int &v = trie[u][p[i] - 'a']; 
		u = v = v ? v : ++idx; 
	} tot[u]++;
}
void bfs() {
	queue<int> q; 
	for(q.push(0); !q.empty(); ) {
		int u = q.front(); q.pop(); 
		for(int c = 0; c < 26; c++) {
			int &v = trie[u][c]; 
			if(!v) v = trie[link[u]][c]; 
			else {
				link[v] = u ? trie[link[u]][c] : 0; 
				tot[v] += tot[link[v]];
				q.push(v);  
			}
		}
	}
}
int match() {
	int u = 0, len = strlen(s); 
	int ret = 0; 
	for(int i = 0; i < len; i++) {
		u = trie[u][s[i] - 'a']; 
		ret += tot[u];
	} return ret; 
}