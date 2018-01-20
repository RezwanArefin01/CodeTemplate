/*////////////////////////////////////////
Persistent Segment Tree 
To make version y from version x write 
root[y] = update(root[x], ... );
To update in a single version x write 
root[x] = update(root[x], ... );
/*////////////////////////////////////////

const int maxn = 1e5+10; 
struct node {
	int l, r, sum; 
} t[maxn * 20]; 
int root[maxn], a[maxn], n, m, k, idx, M;

void update(int &nd, int l, int r, int &i) {
	t[++idx] = t[nd]; 
	++t[nd = idx].sum; //  += v; 
	if(l == r) return; 
	int m = l + r >> 1;
	if(i <= m) update(t[nd].l, l, m, i); 
	else update(t[nd].r, m + 1, r, i);
}

int query(int nd, int l, int r, int &i, int &j) {
	if(r < i || l > j) return 0;
	if(i <= l && r <= j) return t[nd].sum;
	int m = l + r >> 1;
	return query(t[nd].l, l, m, i, j) + query(t[nd].r, m + 1, r, i, j);
}
// a = root[r], b = root[l - 1]
int lesscnt(int a, int b, int l, int r, int k) { 
	if(r <= k) return t[a].sum - t[b].sum; 
	int m = l + r >> 1;
	if(k <= m) return lesscnt(t[a].l, t[b].l, l, m, k);
	else return lesscnt(t[a].l, t[b].l, l, m, k) + 
				lesscnt(t[a].r, t[b].r, m + 1, r, k);
}
int kthnum(int a, int b, int l, int r, int k) {
	if(l == r) return l;
	int cnt = t[t[a].l].sum - t[t[b].l].sum; 
	int m = l + r >> 1;
	if(cnt >= k) return kthnum(t[a].l, t[b].l, l, m, k); 
	else return kthnum(t[a].r, t[b].r, m + 1, r, k - cnt); 
}
void init(int v = 1) {
	t[0].l = t[0].r = t[0].sum = 0;
	for(int i = 1; i <= n; ++i) 
		update(root[i] = root[i - 1], 0, M, a[i]);
}