const int mod = 998244353, g = 3; 
const int N = 1 << 20; 

inline int Pow(int a, int p) {
  int ret = 1; while(p) {
    if(p & 1) ret = (ll) ret * a % mod;
    a = (ll) a * a % mod;
    p >>= 1;
  } return ret;
}


vector<int> rev; 
vector<int> w; 

void prepare(int n) { // n is power of 2
  int sz = __builtin_ctz(n); 
  if(rev.size() != n) {
    rev.assign(n, 0); 
    for(int i = 0; i < n; ++i) {
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1)); 
    }
  }

  if(w.size() >= n) return; 
  if(w.empty()) w = {0, 1}; 
  
  sz = __builtin_ctz(w.size()); 
  w.resize(n);

  // w[n + i] = w_{2n}^i, n power of 2, i < n
  while((1 << sz) < n) {
    int wn = Pow(g, (mod - 1) >> (sz + 1)); 
    for(int i = 1 << (sz - 1); i < (1 << sz); ++i) {
      w[i << 1] = w[i]; 
      w[i << 1 | 1] = (ll) w[i] * wn % mod; 
    } ++sz; 
  }
}

void fft(int *p, int n) {
  prepare(n); 
  for(int i = 1; i < n - 1; ++i) 
    if(i < rev[i]) swap(p[i], p[rev[i]]);
  for(int h = 1; h < n; h <<= 1) {
    for(int s = 0; s < n; s += h << 1) {
      for(int i = 0; i < h; ++i) {
        int &u = p[s + i], &v = p[s + h + i], 
          t = (ll) v * w[h + i] % mod;
        v = u - t < 0 ? u - t + mod : u - t; 
        u = u + t >= mod ? u + t - mod : u + t;
      }
    }
  } 
}

void mul(int *a, int *b, int *c, int n, int m) {
  static int f[N], g[N]; 

  int sz = n + m - 1; 
  while(sz & (sz - 1)) sz = (sz | (sz - 1)) + 1;
  memcpy(f, a, n << 2), memcpy(g, b, m << 2); 
  memset(f + n, 0, sz - n << 2), memset(g + m, 0, sz - n<< 2); 

  fft(f, sz), fft(g, sz); 
  for(int i = 0; i < sz; ++i) 
    f[i] = (ll) f[i] * g[i] % mod; 
  reverse(f + 1, f + sz); 
  fft(f, sz); 

  int inv_n = Pow(sz, mod - 2); 
  for(int i = 0; i < sz; ++i) 
    c[i] = (ll) f[i] * inv_n % mod; 
}

// primitive root, finding the number with order p-1
int primitive_root(int p) {
  vector<int> factor;
  int tmp = p - 1;
  for (int i = 2; i * i <= tmp; ++i) {
    if (tmp % i == 0) {
      factor.push_back(i);
      while (tmp % i == 0) tmp /= i;
    }
  }
  if (tmp != 1) factor.push_back(tmp);
  for (int root = 1;; ++root) {
    bool flag = true;
    for (int i = 0; i < factor.size(); ++i) {
      if (Pow(root, (p - 1) / factor[i], p) == 1) {
        flag = false;
        break;
      }
    }
    if (flag) return root;
  }
}
