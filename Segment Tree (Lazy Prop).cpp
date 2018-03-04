 
int t[maxn<<2], lazy[maxn<<2];
void build(int node, int l, int r) {
	if(l == r) { t[node] = arr[l]; return; } 
	int mid = l + r >> 1;
	build(node << 1, l, mid);
	build(node << 1 | 1, mid + 1, r);
	t[node] = t[node << 1] + t[node << 1 | 1]; 
}
void upd(int node, int l, int r, ll v) {
	lazy[node] += v;
	t[node] += (r - l + 1) * v;
}
void shift(int node, int l, int r) {
	int mid = l + r >> 1;
	upd(node << 1, l, mid, lazy[node]);
	upd(node << 1 | 1, mid + 1, r, lazy[node]);
	lazy[node] = 0;
}
void update(int node, int l, int r, int i, int j, ll v) {
	if(r < i || l > j) return;
	if(i <= l && r <= j) { 
		upd(node, l, r, v);
		return;
	} shift(node, l, r);
	int mid = l + r >> 1;
	update(node << 1, l, mid, i, j, v);
	update(node << 1 | 1, mid + 1, r, i, j, v);
	t[node] = t[node << 1] + t[node << 1 | 1];
}
ll query(int node, int l, int r, int i, int j) {
	if(r < i || l > j) return 0;
	if(i <= l && r <= j) return t[node]; 
	shift(node, l, r);
	int mid = l + r >> 1;
	return query(node << 1, l, mid, i, j) + 
		   query(node << 1 | 1, mid+1, r, i,j);
}