/**********************************
 * Call calcw() in beginning to precalculate all w_pre[] 
 * Call calcrev(sz) before a multiplication. 
 * Take precautions while calculating sz. 
***********************************/

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long double ld; 
ld PI = acos(-1);

struct base {
	ld a, b;
	base(ld _a = 0.0, ld _b = 0.0) : a(_a), b(_b) {}
	const base operator + (const base &c) const 
		{ return base(a + c.a, b + c.b); }
	const base operator - (const base &c) const
		{ return base(a - c.a, b - c.b); }
	const base operator * (const base &c) const
		{ return base(a * c.a - b * c.b, a * c.b + b * c.a); }
	const base conj() const { return base(a, -b); }
}; 

vector<int> rev; 
vector<base> w; 

void prepare(int n) { // n is power of 2
	int sz = __builtin_ctz(n); 
	if(rev.size() != n) {
		rev.assign(n, 0); 
		for(int i = 0; i < n; ++i) {
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1)); 
		}
	}

	if(w.size() >= n) return; 
	if(w.empty()) w = {{0, 0}, {1, 0}}; 
	
	sz = __builtin_ctz(w.size()); 
	w.resize(n);

	// w[n + i] = w_{2n}^i, n power of 2, i < n
	while((1 << sz) < n) {
		double b = 2 * PI / (1 << (sz + 1)), ang = b; 
		for(int i = 0; i < 1 << (sz - 1); ++i, ang += 2 * b) {
			int j = (1 << (sz - 1)) + i; 
			w[2 * j] = w[j]; 
			w[2 * j + 1] = base(cos(ang), sin(ang)); 
		} ++sz; 
	}
}

void fft(base *p, int n) {
	prepare(n); 
	for(int i = 1; i < n - 1; ++i) 
		if(i < rev[i]) swap(p[i], p[rev[i]]);
	for(int h = 1; h < n; h <<= 1) {
		for(int s = 0; s < n; s += h << 1) {
			for(int i = 0; i < h; ++i) {
				base &u = p[s + i], &v = p[s + h + i], 
					t = v * w[h + i];
				v = u - t; u = u + t;
			}
		}
	} 
}

base f[N]; 
void mul(int *a, int *b, int *c, int n, int m) {
	int sz = n + m - 1; 
	while(sz & (sz - 1)) sz = (sz | (sz - 1)) + 1;
	for(int i = 0; i < sz; ++i) 
		f[i] = base(i < n ? a[i] : 0, i < m ? b[i] : 0);
	fft(f, sz); 
	for(int i = 0; i <= (sz >> 1); ++i) {
		int j = (sz - i) & (sz - 1); 
		base x = (f[i] * f[i] - (f[j] * f[j]).conj()) * base(0, -0.25); 
		f[j] = x; f[i] = x.conj(); 
	}
	fft(f, sz); 
	for(int i = 0; i < sz; ++i) c[i] = f[i].a / sz + 0.5; 
}

base f[N], g[N]; 
void mul_mod(int *a, int *b, int *c, int n, int m) {
	int sz = 1;
	while(sz < n + m - 1) sz <<= 1;
	for(int i = 0; i < n; i++) f[i] = base(a[i] & 32767, a[i] >> 15);
	for(int i = 0; i < m; i++) g[i] = base(b[i] & 32767, b[i] >> 15);
	for(int i = n; i < sz; i++) f[i] = base(0, 0); 
	for(int i = m; i < sz; i++) g[i] = base(0, 0); 
	calcrev(sz); 

	fft(f, sz);	fft(g, sz);
	for(int i = 0; i < sz; i++) {
		int j = (sz - i) & (sz - 1);
		base a1 = (f[i] + f[j].conj()) * base(0.5, 0);
		base a0 = (f[i] - f[j].conj()) * base(0, -0.5);
		base b1 = (g[i] + g[j].conj()) * base(0.5 / sz, 0);
		base b0 = (g[i] - g[j].conj()) * base(0, -0.5 / sz);
		u[j] = a1 * b1 + a0 * b0 * base(0, 1);
		v[j] = a1 * b0 + a0 * b1;
	}
	fft(u, sz); fft(v, sz);
	for(int i = 0; i < sz; i++) {
		ll aa = ll(u[i].a + 0.5) % mod, bb = ll(v[i].a + 0.5) % mod, cc = ll(u[i].b + 0.5) % mod; 
		c[i] = ((aa + (bb << 15) % mod) % mod + (cc << 30) % mod) % mod;
	}
}
