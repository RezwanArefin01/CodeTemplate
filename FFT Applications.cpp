/*********************************
 * polyinv(a, b, n) calculates b: b(z)a(z) = 1 (mod z^n)
 * polysqrt(a, b, n) calculates b: b(z)^2 = a(z) (mod z^n)
 * make sure ta[], tb[] has 2n spaces to be used. 
 * in polysqrt(), if a[0] != 1 then discrete sqrt function is needed
**********************************/

void inverse(int *a, int *b, int n) {
  static int x[N], y[N]; 
  b[0] = Pow(a[0], mod - 2);  
  int sz = 1; 
  while(sz < n) {
    sz <<= 1; 
    memcpy(x, a, sz << 2); fft(x, sz); 
    memcpy(y, b, sz << 2); fft(y, sz); 
    for(int i = 0; i < sz; ++i) 
      x[i] = (ll) x[i] * y[i] % mod;
    reverse(x + 1, x + sz);  
    fft(x, sz); 
    for(int i = sz / 2; i < sz; ++i) 
      x[i - sz / 2] = x[i], x[i] = 0; 
    fft(x, sz); 
    for(int i = 0; i < sz; ++i) 
      x[i] = (ll) x[i] * (mod - y[i]) % mod; 
    reverse(x + 1, x + sz); 
    fft(x, sz); 
    int inv_n2 = Pow(sz, mod - 3); 
    for(int i = sz / 2; i < sz; ++i)  
      b[i] = (ll) x[i - sz / 2] * inv_n2 % mod;
  }
}


int inv2 = Pow(2, mod - 2); 
void polysqrt(int *a, int *b, int n) {
	if(n == 1) return void(b[0] = 1); // b[0] = x: x^2 \equiv a[0] 
	polysqrt(a, b, n >> 1); 
	polyinv(b, tb, n);
	for(int i = 0; i < n; ++i) 
		ta[i] = a[i]; 
	for(int i = n; i < (n << 1); ++i) 
		ta[i] = tb[i] = 0; 
	n <<= 1; prepare(n); 
	ntt(ta, n, 0); ntt(tb, n, 0); 
	for(int i = 0; i < n; ++i) 
		ta[i] = (ll) ta[i] * tb[i] % mod;
	ntt(ta, n, 1);
	for(int i = 0; i < n; ++i) 
		b[i] = (ll) inv2 * (ta[i] + b[i]) % mod;
	fill(b + (n >> 1), b + n, 0);
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

void polyinv(int *a, int *b, int n) {
  static int c[N], d[N];
  b[0] = Pow(a[0], mod - 2); 
  int sz = 1;

  while(sz < n) {
    mul_mod(a, b, d, 2 * sz, 2 * sz); 
    for(int i = sz; i < 2 * sz; ++i) 
        d[i - sz] = d[i], d[i] = 0;
    mul_mod(b, d, c, 2 * sz, 2 * sz); 
    for(int i = sz; i < 2 * sz; ++i) {
        b[i] -= c[i - sz];
        if(b[i] < 0) b[i] += mod; 
    }
    sz <<= 1; 
  }
}
