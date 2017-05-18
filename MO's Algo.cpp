const int maxn = 1e5+10;
int n, Q, block, arr[maxn], cnt[maxn], ans[50010];
struct query{
	int l, r, id;
	bool operator < (const query &q) const {
		int a = l/block, b = q.l/block;
		return a == b ? r < q.r : a < b;
	}
} q[50010];
int curr = 0;
void add(int i) {
	cnt[arr[i]]++;
	if(cnt[arr[i]] == 1) curr++;
}
void remove(int i) {
	cnt[arr[i]]--;
	if(cnt[arr[i]] == 0) curr--;
}
void MO() {
	memset(cnt, 0, sizeof cnt);
	block = sqrt(n) + 1;
	sort(q, q+Q);
	int l = 0, r = -1; curr = 0;
	for(int i=0; i<Q; i++) {
		while(l > q[i].l) add(--l);
		while(r < q[i].r) add(++r);
		while(l < q[i].l) remove(l++);
		while(r > q[i].r) remove(r--);
		ans[q[i].id] = curr;
	}
}