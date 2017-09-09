/*////////////////////////////////////////
Persistent Segment Tree 
To make version y from version x write 
root[y] = update(root[x], ... );
To update in a single version x write 
root[x] = update(root[x], ... );
/*////////////////////////////////////////

const int maxn = 1e5 + 10;

int t[maxn * 20], L[maxn * 20], R[maxn * 20], idx = 0, root[maxn]; 
int n, m, arr[maxn]; 

void build(int id, int l, int r) {
	if(l == r) return; 
	L[id] = idx++;
	R[id] = idx++; 
	int mid = l + r >> 1; 
	build(L[id], l, mid);
	build(R[id], mid+1, r); 
}
int update(int id, int l, int r, int i, int v) {
	if(r < i || l > i) return id; 
	int ID = idx++; 
	if(l == r) {
		t[ID] = t[id] + v; 
		return ID;
	} int mid = l + r >> 1; 
	L[ID] = update(L[id], l, mid, i, v);
	R[ID] = update(R[id], mid+1, r, i, v); 

	t[ID] = t[L[ID]] + t[R[ID]];
	return ID;  
}
int query(int id, int l, int r, int i, int j) {
	if(r < i || l > j) return 0;
	if(i <= l && r <= j) return t[id];
	int mid = l + r >> 1;
	return query(L[id], l, mid, i, j) + query(R[id], mid+1, r, i, j); 
}

int lessCount(int l, int r, int k) {
	return query(root[r], 1, n, 1, k-1) - query(root[l-1], 1, n, 1, k-1); 
}

int search(int a, int b, int l, int r, int k) {
	if(l == r) return l; 
	int cnt = t[L[a]] - t[L[b]];
	int mid = l + r >> 1;
	if(cnt >= k) 
		return search(L[a], L[b], l, mid, k);
	return search(R[a], R[b], mid+1, r, k - cnt);
}
int kthnum(int l, int r, int k) {
	return search(root[r], root[l-1], 1, n, k);
}
void init() {
	root[0] = idx++; 
	build(root[0], 1, n); 
	for(int i = 1; i <= n; i++) {
		root[i] = update(root[i-1], 1, n, arr[i], +1);
	}
} 

