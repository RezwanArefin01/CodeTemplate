/**********************************
 * w[0][i][j] = w_{2^i}^j, w[1] is inverse
 * Call calcw() in beginning to precalculate all w[] 
 * Call calcrev(sz) before a multiplication. 
 * Take precautions while calculating sz. 
***********************************/

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

typedef long double ld; 
ld PI = acosl(-1);

struct base {
	ld a, b;
	base(ld _a = 0.0, ld _b = 0.0) : a(_a), b(_b) {}
	const base operator + (const base &c) const 
		{ return base(a + c.a, b + c.b); }
	const base operator - (const base &c) const
		{ return base(a - c.a, b - c.b); }
	const base operator * (const base &c) const
		{ return base(a * c.a - b * c.b, a * c.b + b * c.a); }
}; 

const int N = 1 << 16; 
base w[2][16][N]; 
int rev[N]; 

void calcw() { 	
	for(int d = 0; d < 2; ++d) {
		for(int i = 1; i <= 15; ++i) {
			int l = 1 << i; 
			ld ang = (d ? 2 : -2) * PI / l;
			base wn(cos(ang), sin(ang)); 
			w[d][i][0] = base(1, 0);
			for(int j = 1; j < (l >> 1); ++j) {
				w[d][i][j] = w[d][i][j - 1] * wn;
			}
		}
	} 
} 
void calcrev(int n) {
	int sz = 31 - __builtin_clz(n); 
	for(int i = 1; i < n - 1; ++i) 
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << sz - 1); 
}
void fft(base *p, int n, int dir) {
	for(int i = 1; i < n - 1; ++i) 
		if(i < rev[i]) swap(p[i], p[rev[i]]);
	int lg = 31 - __builtin_clz(n); 
	for(int i = 1; i <= lg; ++i) { int l = 1 << i; 
		for(int j = 0; j < n; j += l) {
			base t, *wn = w[dir][i]; 
			base *u = p + j, *v = u + (l >> 1), *e = v; 
			while(u != e) {
				t = *v * *wn;
				*v = *u - t; 
				*u = *u + t;
				++u, ++v, ++wn;
			}
		}
	} if(dir) for(int i = 0; i < n; ++i) p[i].a /= n, p[i].b /= n;
} 

