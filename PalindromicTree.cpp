char s[N]; // 1-indexed 
int t, idx, tree[N][26], link[N], len[N], occ[N], n;
void extend(int p) {
    while(s[p - len[t] - 1] != s[p]) t = link[t];
    int ch = s[p] - 'a', x = link[t];
    while(s[p - len[x] - 1] != s[p]) x = link[x];
    if(!tree[t][ch]) {
        t[t][ch] = ++idx, len[idx] = len[t] + 2;
        link[idx] = len[idx] == 1 ? 2 : tree[x][ch];
    } t = tree[t][ch], ++occ[t];
}
void build() {
    len[1] = -1, len[2] = 0; 
    link[1] = link[2] = 1;
    t = idx = 2;
    for(int i = 1; i <= n; i++) extend(i); 
    for(int i = idx; i > 2; i--) {
        occ[link[i]] += occ[i];
    } 
}