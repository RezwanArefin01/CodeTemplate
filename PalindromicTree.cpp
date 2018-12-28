char s[N]; // 1-indexed 
int suf, ptr, t[N][26], link[N], len[N], occ[N], n;
void extend(int at) {
    while(s[at - len[suf] - 1] != s[at]) suf=link[suf];
    int ch = s[at] - 'a', tmp = link[suf];
    while(s[at - len[tmp] - 1] != s[at]) tmp=link[tmp];
    if(!t[suf][ch]) {
        t[suf][ch] = ++ptr, len[ptr] = len[suf] + 2;
        link[ptr] = len[ptr] == 1 ? 2 : t[tmp][ch];
    } suf = t[suf][ch], ++occ[suf];
}
void build() {
    len[1] = -1, len[2] = 0; 
    link[1] = link[2] = 1;
    suf = ptr = 2;
    for(int i = 1; i <= n; i++) extend(i); 
    for(int i = idx; i > 2; i--) {
        occ[link[i]] += occ[i];
    } 
}