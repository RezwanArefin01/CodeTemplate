const int N = 1 << 18, mod = 7 * 17 * (1 << 23) + 1, g = 3;
int inv_n;

vector<int> rev, w;

inline int Pow(int a, int p) {
    int ret = 1; while(p) {
        if(p & 1) ret = (ll) ret * a % mod;
        a = (ll) a * a % mod;
        p >>= 1;
    } return ret;
}

inline int mul(int a, int b) {
    return (ll) a * b % mod;
}

void prepare(int n) { // n is power of 2
    int sz = __builtin_ctz(n); 
    if(rev.size() != n) {
        rev.assign(n, 0); 
        for(int i = 0; i < n; ++i) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1)); 
        }
        inv_n = Pow(n, mod - 2);
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
            w[i << 1 | 1] = mul(w[i], wn); 
        } ++sz; 
    }
}

void ntt(int *p, int n, int inv = 0) {
    prepare(n); 
    for(int i = 1; i < n - 1; ++i) 
        if(i < rev[i]) swap(p[i], p[rev[i]]);
    for(int h = 1; h < n; h <<= 1) {
        for(int s = 0; s < n; s += h << 1) {
            for(int i = 0; i < h; ++i) {
                int &u = p[s + i], &v = p[s + h + i], 
                    t = mul(v, w[h + i]);
                v = u - t; u = u + t;
                if(v < 0) v += mod;
                if(u >= mod) u -= mod;
            }
        }
    } 
}
// a, b are destroyed
void mul(int *a, int *b, int *c, int n, int m) {
    int sz = 1; 
    while(sz < n + m - 1) sz <<= 1; 
    ntt(a, sz); ntt(b, sz); 
    for(int i = 0; i < sz; ++i) 
        c[i] = mul(a[i], b[i]);
    reverse(c + 1, c + sz); 
    ntt(c, sz); 
    int inv_n = Pow(sz, mod - 2); 
    for(int i = 0; i < sz; ++i) 
        c[i] = mul(c[i], inv_n);
}

// primitive root, finding the number with order p-1 
int primitive_root(int p) {
    vector<int> factor;
    int tmp = p - 1;
    for(int i = 2; i * i <= tmp; ++i) {
        if (tmp % i == 0) {
            factor.push_back(i);
            while (tmp % i == 0) tmp /= i;  
        }   
    }
    if(tmp != 1) factor.push_back(tmp);
    for(int root = 1; ; ++root) {
        bool flag = true;
        for(int i = 0; i < factor.size(); ++i) {
            if(Pow(root, (p - 1) / factor[i], p) == 1) {
                flag = false;   
                break;
            }
        }
        if (flag) return root;
    }
}