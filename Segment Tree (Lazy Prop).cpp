
void upd(int node, int l, int r, ll v) {
	lazy[node] += v;
	tree[node] += (r-l+1)*v;
}
void shift(int node, int l, int r) {
	int mid = l + r >> 1;
	upd(node<<1, l, mid, lazy[node]);
	upd(node<<1|1, mid+1, r, lazy[node]);
	lazy[node] = 0;
}
void update(int node, int l, int r, int i, int j, ll v) {
	if(r < i || l > j) return;
	if(i <= l && r <= j) {
		upd(node, l, r, v);
		return;
	} shift(node, l, r);
	int mid = l + r >> 1;
	int left = node<<1, right = left|1;
	update(left, l, mid, i, j, v);
	update(right, mid+1, r, i, j, v);
	tree[node] = tree[left] + tree[right];
}
ll query(int node, int l, int r, int i, int j) {
	if(r < i || l > j) return 0;
	if(i <= l && r <= j) {
		return tree[node]; 
	} shift(node, l, r);
	int mid = l + r >> 1;
	int left = node<<1, right = left|1;
	return query(left, l, mid, i, j) + 
		   query(right, mid+1, r, i,j);
}