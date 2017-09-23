#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> ii; 

const int maxn = 1e5+10;
int block, n, m;
int a[maxn], last[maxn], angry[maxn]; 

struct query {
	int l, r, t, id; 
	bool operator < (const query &p) const {
		int a = l / block, b = p.l/block;
		return a == b ? r < p.r : a < b;	
	}
} q[maxn]; 

struct update {
	int x, pre, now;  
} u[maxn];

ll sum, ans[maxn]; 
int cnt[maxn];
int l, r, t; 

void add(int x) { sum += (ll) a[x] * angry[++cnt[a[x]]]; }
void remove(int x) { sum -= (ll) a[x] * angry[cnt[a[x]]--]; }

void apply(int x, int y) {
	if(l <= x && x <= r) {
		remove(x); 
		a[x] = y;
		add(x); 
	} else a[x] = y; 
}
int main(int argc, char const *argv[]) {
	#ifdef LOCAL_TESTING
		freopen("in", "r", stdin);
	#endif
	scanf("%d", &n);

	for(int i = 0; i < n; i++) 
		scanf("%d", &a[i]), last[i] = a[i];

	for(int i = 1; i <= n; i++) 
		scanf("%d", &angry[i]);

	scanf("%d", &m);
	int Q = 0, U = 0;
	for(int i = 0; i < m; i++) {
		int t, l, r; 
		scanf("%d %d %d", &t, &l, &r); l--;
		if(t == 1) { r--;
			q[Q] = {l, r, U, Q};
			Q++;
		} else { 
			u[++U] = {l, last[l], r};
			last[l] = r;
		}
	}
	block = 320;
	sort(q, q+Q);

	l = 0, r = -1, t = 0;
	for(int i = 0; i < Q; i++) {
		while(t < q[i].t) t++, apply(u[t].x, u[t].now);
		while(t > q[i].t) apply(u[t].x, u[t].pre), t--; 

		while(l > q[i].l) add(--l);
		while(r < q[i].r) add(++r);
		while(l < q[i].l) remove(l++);
		while(r > q[i].r) remove(r--);

		ans[q[i].id] = sum;
	}
	for(int i = 0; i < Q; i++) {
		printf("%lld\n", ans[i]);
	}	
}