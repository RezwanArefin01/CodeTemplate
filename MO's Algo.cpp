const int maxn = 1e5+10;
int n, Q, block, arr[maxn], cnt[maxn], ans[maxn];
struct query{
	int l, r, id;
	bool operator < (const query &q) const {
		int a = l/block, b = q.l/block;
		return a == b ? r < q.r : a < b;
	}
} q[maxn];
int curr = 0;

void add(int i) {
	int x = arr[i];
	cnt[x]++;
	if(cnt[x] == 1) curr++;
}
void remove(int i) {
	int x = arr[i];
	cnt[x]--;
	if(cnt[x] == 0) curr--;
}
void MO() {
	block = sqrt(n) + 1;
	sort(q, q + m);
	int l = 0, r = -1; curr = 0;
	for(int i = 0; i < m; i++) {
		while(l > q[i].l) add(--l);
		while(r < q[i].r) add(++r);
		while(l < q[i].l) remove(l++);
		while(r > q[i].r) remove(r--);
		ans[q[i].id] = curr;
	}
}