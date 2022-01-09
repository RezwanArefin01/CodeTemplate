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
    double ang = 2 * PI / (1 << (sz + 1)); 
    base wn(cos(ang), sin(ang));
    // For NTT: wn = Pow(g, (mod - 1) >> (sz + 1)); 
    for(int i = 1 << (sz - 1); i < (1 << sz); ++i) {
      w[i << 1] = w[i]; 
      w[i << 1 | 1] = w[i] * wn; 
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

void mul(int *a, int *b, int *c, int n, int m) {
  static base f[N]; 
  
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

inline void mul_mod(int *a, int *b, int *c, int n, int m) {
  static base f[N], g[N], u[N], v[N];
  int sz = 1;
  while(sz < n + m - 1) sz <<= 1;
  for(int i = 0; i < n; i++) f[i] = base(a[i] & 32767, a[i] >> 15);
  for(int i = 0; i < m; i++) g[i] = base(b[i] & 32767, b[i] >> 15);
  for(int i = n; i < sz; i++) f[i] = base(0, 0); 
  for(int i = m; i < sz; i++) g[i] = base(0, 0); 

  fft(f, sz), fft(g, sz);
  for(int i = 0; i < sz; ++i) {
    int j = (sz - i) & (sz - 1);
    static base da, db, dc, dd;
    da = (f[i] + f[j].conj()) * base(0.5, 0);
    db = (f[i] - f[j].conj()) * base(0, -0.5);
    dc = (g[i] + g[j].conj()) * base(0.5, 0);
    dd = (g[i] - g[j].conj()) * base(0, -0.5);
    u[j] = da * dc + da * dd * base(0, 1); 
    v[j] = db * dc + db * dd * base(0, 1);
  }
  fft(u, sz), fft(v, sz);
  for(int i = 0; i < sz; ++i) {
    int da = (ll)(u[i].a / sz + 0.5) % mod;
    int db = (ll)(u[i].b / sz + 0.5) % mod;
    int dc = (ll)(v[i].a / sz + 0.5) % mod;
    int dd = (ll)(v[i].b / sz + 0.5) % mod;
    c[i] = (da + ((ll)(db + dc) << 15) + ((ll)dd << 30)) % mod;
  }
}