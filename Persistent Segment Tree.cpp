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
};
node *root[100000];