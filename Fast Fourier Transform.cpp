typedef long double ld; 
ld PI = acosl(-1);
typedef long long ll;
typedef pair<int, int> ii; 

struct base {
	ld a, b;
	base(ld a = 0, ld b = 0) : a(a), b(b) {}
	const base operator + (const base &c) const 
		{ return base(a + c.a, b + c.b); }
	const base operator - (const base &c) const
		{ return base(a - c.a, b - c.b); }
	const base operator * (const base &c) const
		{ return base(a * c.a - b * c.b, a * c.b + b * c.a); }
};
void fft(vector<base> &p, bool inv = 0) { 
	int n = p.size(), i = 0; 
	for(int j = 1; j < n - 1; ++j) {
		for(int k = n >> 1; k > (i ^= k); k >>= 1);
		if(j < i) swap(p[i], p[j]);
	}
	for(int l = 1, m; (m = l << 1) <= n; l <<= 1) {
		ld ang = 2 * PI / m;
		base wn = base(cos(ang), (inv ? 1. : -1.) * sin(ang)), w;
		for(int i = 0, j, k; i < n; i += m) {
			for(w = base(1, 0), j = i, k = i + l; j < k; ++j, w = w * wn) {
				base t = w * p[j + l]; 
				p[j + l] = p[j] - t; 
				p[j] = p[j] + t;
			}
		}
	}
	if(inv) for(int i = 0; i < n; ++i) p[i].a /= n, p[i].b /= n;
}
vector<int> multiply(vector<int> &a, vector<int> &b) {
	int n = a.size(), m = b.size(), t = n + m - 1, sz = 1; 
	while(sz < t) sz <<= 1;
	vector<base> x(sz), y(sz), z(sz); 
	for(int i = 0 ; i < sz; ++i) {
		x[i] = i < a.size() ? base(a[i], 0) : base(0, 0); 
		y[i] = i < b.size() ? base(b[i], 0) : base(0, 0); 
	} fft(x), fft(y);
	for(int i = 0; i < sz; ++i) z[i] = x[i] * y[i];
	fft(z, 1);
	vector<int> ret(sz);
	for(int i = 0; i < sz; ++i) ret[i] = z[i].a + 0.5;
	return ret;
}