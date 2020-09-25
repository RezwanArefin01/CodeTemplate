const int N = 3e5 + 5;

int tree[N][26], t, sz, len[N], link[N];
int slink[N], diff[N]; // not required for all problems
char s[N];

void extend(int p) {
  while (s[p - len[t] - 1] != s[p]) t = link[t];
  int x = link[t];
  while (s[p - len[x] - 1] != s[p]) x = link[x];
  int c = s[p] - 'a';
  if (!tree[t][c]) {
    tree[t][c] = ++sz;
    len[sz] = len[t] + 2;
    link[sz] = len[sz] == 1 ? 2 : tree[x][c];
    diff[sz] = len[sz] - len[link[sz]];
    if (diff[sz] == diff[link[sz]])
      slink[sz] = slink[link[sz]];
    else
      slink[sz] = link[sz];
  }
  t = tree[t][c];
}

void build() {
  len[1] = -1, len[2] = 0;
  link[1] = link[2] = 1;
  t = idx = 2;
  for (int i = 1; i <= n; i++) extend(i);
  for (int i = idx; i > 2; i--) {
    occ[link[i]] += occ[i];
  }
}

void dp_on_suffixes() { 
  for(int i = 1; i <= n; ++i) {
    extend(i); 
    for(int u = t; len[u] > 0; u = slink[u]) {
      dp[u] = ans[i - len[slink[u]] - diff[u]]; 
      if(diff[u] == diff[link[u]]) 
        dp[u] = min(dp[u], dp[link[u]]); 
      ans[i] = min(ans[i], dp[u] + 1); 
    }
  }
}