#include <bits/stdc++.h>
using namespace std;

#define left lol
typedef long long ll;
typedef pair<int, int> ii; 

const int N = 1e5 + 10; 

int n, Q, a[N], blc[N], ans[N], c;  

struct query {
	int l, r, id; 
	query(int l = 0, int r = 0, int id = 0): 
		l(l), r(r), id(id) {} 
	bool operator < (const query &q) const {
		return blc[l] == blc[q.l] ? ((r < q.r) ^ (blc[l] & 1)) : l < q.l; 
	}
} q[N]; 

inline void add(int x) { }
inline void remove(int x) { }

int main(int argc, char const *argv[]) {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]); 
	}

	scanf("%d", &Q); 
	for(int i = 1; i <= Q; i++) {
		scanf("%d %d", &q[i].l, &q[i].r); 
		q[i].id = i; 
	}

	int sz = n / sqrt(Q); 
	for(int i = 1; i <= n; ++i) blc[i] = i / sz; 
	sort(q + 1, q + Q + 1); 

	int l = 1, r = 0;
	for(int i = 1; i <= Q; ++i) {
		while(r < q[i].r) add(a[++r]); 
		while(l > q[i].l) add(a[--l]); 
		while(r > q[i].r) remove(a[r--]); 
		while(l < q[i].l) remove(a[l++]); 
		ans[q[i].id] = c; 
	}

	for(int i = 1; i <= Q; ++i) {
		printf("%d\n", ans[i]);
	}
}