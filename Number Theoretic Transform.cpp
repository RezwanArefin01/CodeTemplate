ll mod = 25 * (1 << 22) + 1; 
ll g = 3, w[1 << 22];

ll Pow(ll n, ll p) {
	if(!p) return 1; 
	else if(p & 1) return n * Pow(n, p - 1) % mod;
	else {
		ll v = Pow(n, p / 2);
		return (v * v) % mod;
	}
}

void ntt(vector<ll> &p, bool inv = 0) {
	int n = p.size(), i = 0;
	for(int j = 1; j < n - 1; ++j) {
		for(int k = n >> 1; k > (i ^= k); k >>= 1);
		if(j < i) swap(p[i], p[j]);
	}
	ll r = Pow(g, (mod - 1) / n);
	if(inv) r = Pow(r, mod - 2);
	
	w[0] = 1; 
	for(int i = 1; i <= n; i++) 
		w[i] = w[i - 1] * r % mod; 

	for(int l = 1, m; (m = l << 1) <= n; l <<= 1) {
		for(int i = 0; i < n; i += m) {
			for(int j = i, add = n / m, z = 0; j < i + l; ++j, z += add) {
				ll t = p[j + l] * w[z] % mod;
				p[j + l] = p[j] - t + mod; p[j] += t;
				if(p[j + l] >= mod) p[j + l] -= mod;
				if(p[j] >= mod) p[j] -= mod;
			}
		}
	} if(inv) {
		ll t = Pow(n, mod - 2);
		for(int i = 0; i < n; i++) 
			p[i] = p[i] * t % mod;
	} 
}

vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
	int n = a.size(), m = b.size(), t = n + m - 1, sz = 1; 
	while(sz < t) sz <<= 1;
	a.resize(sz); b.resize(sz);
	ntt(a), ntt(b);
	for(int i = 0; i < sz; ++i) 
		a[i] = a[i] * b[i] % mod; 
	ntt(a, 1); 
	return a; 
}