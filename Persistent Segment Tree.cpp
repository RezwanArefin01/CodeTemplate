/*////////////////////////////////////////
Persistent Segment Tree 
To make version y from version x write 
root[y] = root[x] -> update(...);
To update in a single version x write 
root[x] = root[x] -> update(...);
/*////////////////////////////////////////
struct node {
	ll val; 
	node *left, *right; 
	node(ll _val = 0, node *_left = NULL, node *_right = NULL) : 
		val(_val), left(_left), right(_right){}

	void build(int l, int r) {
		if(l == r) return; 
		left = new node(); 
		right = new node();
		int mid = l + r >> 1;
		left -> build(l, mid);
		right -> build(mid+1, r);
	}
	node *update(int l, int r, int idx, ll v) {
		if(r < idx || l > idx) return this; 
		if(l == r) {
			node *p = new node(val, left, right);
			p -> val += v;
			return p;
		} int mid = l + r >> 1;
		node *p = new node(val);
		p -> left = left -> update(l, mid, idx, v);
		p -> right = right -> update(mid+1, r, idx, v);
		p -> val = p -> left -> val + p -> right -> val;
		return p;
	}
	ll query(int l, int r, int i, int j) {
		if(r < i || l > j) return 0;
		if(i <= l && r <= j) return val;
		int mid = l + r >> 1;
		return left -> query(l, mid, i, j) + 
			  right -> query(mid+1,r,i, j);
	} 
} *root[100000];
int lessCount(int l, int r, int k) {
	int ret = root[r] -> query(0, n-1, 0, k-1); 
	if(l - 1 >= 0) 
		ret -= root[l-1] -> query(0, n-1, 0, k-1); 
	return ret;
}
int search(node *a, node *b, int l, int r, int k) {
	if(l == r) return l;
	int cnt = a -> left -> val - b -> left -> val;
	int mid = l + r >> 1;
	if(cnt >= k) 
		return search(a -> left, b -> left, l, mid, k);
	else return search(a -> right, b -> right, mid+1, r, k - cnt); 
}
int kthnum(int l, int r, int k) {
	node *null = new node(0, NULL, NULL);
	null -> left = null -> right = null; 
	node *a = root[r];
	node *b = (l - 1 >= 0) ? root[l-1] : null; 
	return search(a, b, 0, n-1, k);
}
void init(int arr[]) {
	root[0] = new node(); 
	root[0] -> build(0, n-1); 
	root[0] = root[0] -> update(0, n-1, arr[0], +1);
	for(int i = 1; i < n; i++) 
		root[i] = root[i-1] -> update(0, n-1, arr[i], +1);
}
