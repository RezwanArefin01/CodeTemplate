struct node {
	int size, prior, key; 
	node *l, *r; 
	node(int v = 0) {
		size = 1; prior = rand(); key = v;
		l = r = NULL;
	}
} *root;
typedef node* pnode; 

int sz(pnode t) { 
	return t ? t -> size : 0; 
}
void upd_sz(pnode t) {
	if(t) t -> size = sz(t -> l) + sz(t -> r) + 1;
} 
void split(pnode t, pnode &l, pnode &r, int k) {
	if(!t) l = r = NULL;
	else if(t -> key <= k) 
		split(t -> r, t -> r, r, k), l = t;
	else split(t -> l, l, t -> l, k), r = t;
	upd_sz(t);
}
void merge(pnode &t, pnode l, pnode r) {
	if(!l || !r) t = l ? l : r; 
	else if(l -> prior > r -> prior) 
		merge(l -> r, l -> r, r), t = l;
	else merge(r -> l, l, r -> l), t = r;
	upd_sz(t);
}
void insert(pnode &t, pnode it) {
	if(!t) t = it;
	else if(t -> prior < it -> prior) 
		split(t, it -> l, it -> r, it -> key), t = it;
	else insert(it -> key <= t -> key ? t -> l : t -> r, it);
	upd_sz(t);
}
void erase(pnode &t, int key) {
	if(!t) return; 
	else if(t -> key == key) {
		pnode tmp = t; 
		merge(t, t -> l, t -> r);
		free(tmp);
	} else erase(key <= t -> key ? t -> l : t -> r, key);
	upd_sz(t);	
}
int countLess(int x) {
	pnode l, r; 
	split(root, l, r, x-1);
	int ret = sz(l);
	merge(root, l, r); 
	return ret;
}
int kth(pnode t, int k) {
	int cnt = sz(t -> l); 
	if(cnt == k - 1) return t -> key; 
	else if(cnt >= k) return kth(t -> l, k);
	else return kth(t -> r, k - cnt - 1);
}
void insert(int x) {
	insert(root, new node(x));
}
bool find(pnode t, int key) {
	if(!t) return 0; 
	if(t -> key == key) return 1; 
	else if(key <= t -> key) return find(t -> l, key);
	else return find(t -> r, key);
}