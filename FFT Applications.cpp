/*********************************
 * polyinv(a, b, n) calculates b: b(z)a(z) = 1 (mod z^n)
 * polysqrt(a, b, n) calculates b: b(z)^2 = a(z) (mod z^n)
 * make sure ta[], tb[] has 2n spaces to be used. 
 * in polysqrt(), if a[0] != 1 then discrete sqrt function is needed
**********************************/

void mul(int *a, int *b, int *c, int n, int m) {
  static int f[N], g[N]; 

  int sz = n + m - 1; 
  while(sz & (sz - 1)) sz = (sz | (sz - 1)) + 1;
  memcpy(f, a, n << 2), memcpy(g, b, m << 2); 
  memset(f + n, 0, sz - n << 2), memset(g + m, 0, sz - n << 2); 

  fft(f, sz), fft(g, sz); 
  for(int i = 0; i < sz; ++i) 
    f[i] = (ll) f[i] * g[i] % mod; 
  reverse(f + 1, f + sz); 
  fft(f, sz); 

  int inv_n = Pow(sz, mod - 2); 
  for(int i = 0; i < sz; ++i) 
    c[i] = (ll) f[i] * inv_n % mod; 
}

// a[0] != 0, a has degee (deg - 1), first n terms of inverse.
void polyinv(int *a, int *b, int deg, int n) { 
  static int x[N], y[N]; 
  b[0] = Pow(a[0], mod - 2);  
  int sz = 1; 
  while(sz < n) {
    sz <<= 1; 
    for(int i = 0; i < sz; ++i) x[i] = i < deg ? a[i] : 0; 
    for(int i = 0; i < sz; ++i) y[i] = 2 * i < sz ? b[i] : 0; 
    fft(x, sz), fft(y, sz); 
    for(int i = 0; i < sz; ++i) x[i] = mul(x[i], y[i]); 
    reverse(x + 1, x + sz), fft(x, sz);
    for(int i = sz / 2; i < sz; ++i) x[i - sz / 2] = x[i], x[i] = 0; 
    fft(x, sz); 
    for(int i = 0; i < sz; ++i) x[i] = mul(x[i], mod - y[i]); 
    reverse(x + 1, x + sz), fft(x, sz); 
    int inv_n2 = Pow(sz, mod - 3); 
    for(int i = sz / 2; i < sz; ++i) b[i] = mul(x[i - sz / 2], inv_n2); 
  }
}

// a[0] = 1, a has degee (deg - 1), first n terms of ln.
void polyln(int *a, int *b, int deg, int n) {
  static int c[N], inv[N]; 
  if(!inv[1]) { 
    inv[1] = 1; 
    for(int i = 2; i < N; ++i) // change n as needed. 
      inv[i] = mul(mod - mod / i, inv[mod % i]);
  }
  polyinv(a, c, deg, n); 
  for(int i = 0; i < n; ++i) b[i] = mul(i + 1, i + 1 < deg ? a[i + 1] : 0); 
  mul(b, c, b, n, n);
  for(int i = n - 1; i > 0; --i) b[i] = mul(b[i - 1], inv[i]); 
  b[0] = 0; 
}


// a[0] = 0. a has degree (deg - 1). 
void polyexp(int *a, int *b, int deg, int n) {
  static int x[N], y[N]; 
  b[0] = 1;
  int sz = 1; 
  while(sz < n) {
    sz <<= 1; 
    for(int i = 0; i < sz; ++i) x[i] = 2 * i < sz ? b[i] : 0; 
    fft(x, sz), polyln(b, y, sz / 2, sz); 
    for(int i = sz / 2; i < sz; ++i) {
      int t = i < deg ? a[i] : 0; 
      y[i - sz / 2] = t - y[i] < 0 ? t - y[i] + mod : t - y[i], y[i] = 0; 
    }
    fft(y, sz); 
    for(int i = 0; i < sz; ++i) x[i] = mul(x[i], y[i]); 
    reverse(x + 1, x + sz); 
    fft(x, sz); 
    int inv_n = Pow(sz, mod - 2); 
    for(int i = sz / 2; i < sz; ++i) b[i] = mul(x[i - sz / 2], inv_n); 
  }
}


// first n terms of a^k. 
void polypow(int *a, int *b, int deg, int k, int n) {
  static int c[N];
  memset(b, 0, n << 2); 
  int m = 0; 
  while(m < deg && a[m] == 0) ++m; 
  if((ll) m * k > n) return; 
  int leading = a[m], inv = Pow(leading, mod - 2), scale = Pow(leading, k); 
  for(int i = m; i < deg; ++i) a[i] = mul(a[i], inv); 
  polyln(a + m, c, deg - m, n - m * k); 
  for(int i = 0; i < n - m * k; ++i) c[i] = mul(c[i], k); 
  polyexp(c, b + m * k, n - m * k, n - m * k); 
  for(int i = m * k; i < n; ++i) b[i] = mul(b[i], scale); 
}


// used in polysqrt. 
ll shanks(ll a, ll b, ll m) { 
  a %= m, b %= m; ll n = sqrt(m) + 1; 
  unordered_map<ll, ll> mp; 
  ll an = 1, base = 1, ans = -1;
  for(int i = 0; i < n; i++) an = (an * a) % m; 
  for(int i = 1; i <= n; i++) {
    base = (base * an) % m; 
    if(!mp.count(base)) 
      mp[base] = i;
  } base = b; 
  for(int j = 0; j <= n; j++) {
    if(mp.count(base)) {
      ll ret = mp[base] * n - j;
      if(ans == -1 || (ret < m && ans > ret)) ans = ret; 
    } base = (base * a) % m;
  } return ans;
}
 

// CAUTION: assumes a, b is clear. a[0] = 1. 
void polysqrt_monic(int *a, int *b, int deg, int n) {
  static int x[N], y[N];  
  b[0] = 1; 
  int sz = 2; 
  while(sz / 2 < n) {
    sz <<= 1; 
    for(int i = 0; i < sz / 2; ++i) x[i] = i < deg ? a[i] : 0; 
    polyinv(b, y, sz >> 1, sz >> 1);
    fft(x, sz), fft(y, sz);
    for(int i = 0; i < sz; ++i) x[i] = mul(x[i], y[i]); 
    reverse(x + 1, x + sz); 
    fft(x, sz); 
    int inv_n = Pow(sz, mod - 2); 
    for(int i = (sz >> 2); i < (sz >> 1); ++i) 
      b[i] = mul((mod + 1) / 2, b[i] + mul(x[i], inv_n));
  }
}

// CAUTION: assumes a, b is clear. 
bool polysqrt(int *a, int *b, int deg, int n) {
  static int x[N], y[N], z[N];
  memset(b, 0, n << 2); 

  int m = 0; 
  while(m < deg && a[m] == 0) ++m; 
  if(m == deg) return 1; // b = {0}
  if(m & 1) return 0;  

  int lg = shanks(mul(g, g), a[m], mod), scale = Pow(a[m], mod - 2); 
  if(lg == -1) return 0; 
  for(int i = m; i < deg; ++i) a[i] = mul(a[i], scale); 

  polysqrt_monic(a + m, b + m / 2, deg - m, n - m / 2); 
  scale = Pow(g, lg); 
  for(int i = m / 2; i < n; ++i) b[i] = mul(b[i], scale); 
  return 1; 
}

// Raising factorials. 
// (x+1)(x+2)...(x+N)

int f[M], h[M], a[M], b[M]; 
int fact[M], inv[M];

void build(int n) {
  if(n == 1) return void(f[0] = f[1] = 1); 
	if(n & 1) {
		build(n - 1); 
      for(int i = n; i >= 1; i--) {
        f[i] = f[i - 1] + (ll) n * f[i] % mod; 
        if(f[i] >= mod) f[i] -= mod; 
      } f[0] = (ll) f[0] * n % mod; 
      return; 
	} 
    n >>= 1; build(n); 
	int t = n + n + 1, sz = 1; 
	while(sz < t) sz <<= 1; 
	prepare(sz); 

	for(int i = 0; i <= n; i++) 
		a[i] = (ll) f[n - i] * fact[n - i] % mod; 
	for(int i = 0, p = 1; i <= n; i++) {
		b[i] = (ll) p * inv[i] % mod; 
		p = (ll) p * n % mod; 
	}
  for(int i = n + 1; i < sz; i++) a[i] = b[i] = 0; 

	ntt(a, sz); ntt(b, sz); 
	for(int i = 0; i < sz; i++) 
		h[i] = (ll) a[i] * b[i] % mod;
	ntt(h, sz, 1); 
	reverse(h, h + n + 1); 

	for(int i = 0; i <= n; i++) 
		h[i] = (ll) h[i] * inv[i] % mod;
	for(int i = n + 1; i < sz; i++) 
		f[i] = h[i] = 0; 

	ntt(h, sz); ntt(f, sz); 
	for(int i = 0; i < sz; i++) 
		f[i] = (ll) f[i] * h[i] % mod; 
	ntt(f, sz, 1);
}

// q_i = P(x^i), for i in [0..m-1]
void chirpz(int *p, int *q, int n, int m, int x) {
  static int a[N], b[N], c[N];
  int t = n + m, s = max(n, m);
  int xinv = Pow(x, mod - 2);
  for (int i = 0; i < s; ++i) q[i] = Pow(xinv, (ll)i * (i - 1) / 2 % (mod - 1));
  for (int i = 0; i < n; ++i) a[n - i - 1] = mul(p[i], q[i]);
  for (int i = n; i < t; ++i) a[i] = 0;
  for (int i = 0; i < t; ++i) b[i] = Pow(x, (ll)i * (i - 1) / 2 % (mod - 1));
  mul(a, b, c, t, t);
  for (int i = 0; i < m; ++i) q[i] = mul(q[i], c[n + i - 1]);
}

// c[k] = sum a[i] * b[i + k] 
void dot(int *a, int *b, int *c, int n, int m) {
  for(int i = 0; i < n; ++i) c[i] = a[n - 1 - i]; 
  mul(c, b, c, n, m); 
  for(int i = 0; i < m; ++i) c[i] = c[n - 1 + i]; 
}
