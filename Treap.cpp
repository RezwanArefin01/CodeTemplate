struct node {
	int size, prior, val;
	node *left, *right; 
	node(){} 
	node(int val) {
		size = 1;
		this->val = val; 
		prior = rand(); 
		left = right = NULL; 
	}
} *root;
typedef node* pnode; 

int sz(pnode t) {
	return t?t->size:0; 
}
void update(pnode t) { 
	if(t) t->size = 1 + sz(t->left) + sz(t->right); 
}

void split(pnode t, pnode &l, pnode &r, int k) {
	if(!t) l = r = NULL; 
	else if(t->val <= k) 
		split(t->right, t->right, r, k), l = t; 
	else split(t->left, l, t->left, k), r = t; 
	update(t); 
}
void merge(pnode &t, pnode l, pnode r) {
	if(!l || !r) t = l ? l : r; 
	else if(l->prior > r->prior) 
		merge(l->right, l->right, r), t = l; 
	else merge(r->left, l, r->left), t = r; 
	update(t); 
}

bool find(pnode t, int val) {
	if(!t) return 0;
	else if(t->val == val) return 1; 
	else if(val <= t->val) 
		return find(t->left, val); 
	else return 
		find(t->right, val); 
}

void insert(pnode &t, pnode it) {
	if(!t) t = it;
	else if(it->prior > t->prior) {
		split(t, it->left, it->right, it->val); 
		t = it; 
	} else insert(it->val <= t->val ? t->left : t->right, it); 
	update(t);
} 

void erase(pnode &t, int val) {
	if(!t) return; 
	else if(val == t->val) {
		pnode tmp = t; 
		merge(t, t->left, t->right); 
		free(tmp); 
	} else {
		erase(val <= t->val ? t->left : t->right, val); 
	} update(t); 
}

void insert(int num) {
	pnode x = new node(num); 
	insert(root, x); 
} 

int countLess(int x) {
	pnode l, r; 
	split(root, l, r, x-1); 
	int ans = sz(l); 
	merge(root, l, r); 
	return ans; 
}
int kth(pnode t, int k) {
	int cntleft = sz(t->left); 
	if(cntleft == k-1) return t->val; 
	else if(cntleft >= k) {
		return kth(t->left, k);  
	} else return kth(t->right, k - cntleft - 1); 
} 