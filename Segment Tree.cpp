
int tree[maxn<<2];
void build(int node, int l, int r) {
	if(l == r) { tree[node] = arr[l]; return; } 
	int mid = l + r >> 1;
	build(node<<1, l, mid);
	build(node<<1|1, mid+1, r);
	tree[node] = tree[node<<1] + tree[node<<1|1]; 
}
void update(int node, int l, int r, int i, int j, ll v) {
	if(r < i || l > j) return;
	if(i <= l && r <= j) {
		tree[node] += v; 
		return; 
	} int mid = l + r >> 1;
	update(node << 1, l, mid, i, j, v);
	update(node << 1|1, mid+1, r, i, j, v);
	tree[node] = tree[node << 1] + tree[node << 1 | 1];
}
ll query(int node, int l, int r, int i, int j) {
	if(r < i || l > j) return 0;
	if(i <= l && r <= j) {
		return tree[node]; 
	} int mid = l + r >> 1;
	return query(node << 1, l, mid, i, j) + 
		   query(node << 1|1, mid+1, r, i,j);
}