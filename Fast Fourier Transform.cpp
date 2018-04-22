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
}; 

const int N = 1 << 20; 
base w_pre[N|1], w[N|1]; int rev[N];

void calcw() { 	
	for(int i = 0; i <= N; ++i) 
		w_pre[i] = base(cos(2*PI/N*i), sin(2*PI/N*i));
}    
void calcrev(int n) {
	int sz = 31 - __builtin_clz(n); sz = abs(sz);
	for(int i = 1; i < n - 1; ++i) 
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << sz - 1); 
}
void fft(base *p, int n, int dir) {
	for(int i = 1; i < n - 1; i++) 
		if(i < rev[i]) swap(p[i], p[rev[i]]);
	for(int h = 1; h < n; h <<= 1) { int l = h << 1; 
		if(!dir) for(int j = 0; j < h; ++j) w[j] = w_pre[N/l*j]; 
		else for(int j = 0; j < h; ++j) w[j] = w_pre[N-N/l*j];
		for(int j = 0 ; j < n; j += l) {
			base t, *wn = w; 
			base *u = p + j, *v = u + h, *e = v; 
			while(u != e) {
				t = *v * *wn;
				*v = *u - t; 
				*u = *u + t;
				++u, ++v, ++wn;
			}
		}
	} if(dir) for(int i = 0; i < n; ++i) p[i].a /= n, p[i].b /= n;
} 
