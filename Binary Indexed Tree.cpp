
struct BIT {
	vector<ll> A, M; int sz; 
	void init(int n) {
		A = M = vector<ll>(n + 5, 0); 
		sz = n; 
	}
	void upd(int x, ll m, ll a) {
		for(; x <= sz; x += x & -x) 
			M[x] += m, A[x] += a;
	}
	void update(int l, int r, ll v) {
		upd(l, v, -(l - 1) * v); 
		upd(r, -v, r * v);
	}
	ll query(int idx) {
		ll mul = 0, add = 0;
		for(int x = idx; x > 0; x -= x & -x) 
			mul += M[x], add += A[x]; 
		return mul * idx + add; 
	}
	ll query(int l, int r) {
		return query(r) - query(l - 1); 
	}
} t;