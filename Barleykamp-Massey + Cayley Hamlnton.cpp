 vector<ll> BerlekampMassey(vector<ll> s) {
    int n = s.size(), L = 0, m = 0;
    vector<ll> C(n), B(n), T;
    C[0] = B[0] = 1;
    ll b = 1;
    for(int i = 0; i < n; ++i) { 
        ++m;
        ll d = s[i] % mod;
        for(int j = 1; j <= L; ++j) 
            d = (d + C[j] * s[i - j]) % mod;
        if (!d) continue;
        T = C; ll coef = d * Pow(b, mod-2) % mod;
        for(int j = m; j < n; ++j) 
            C[j] = (C[j] - coef * B[j - m]) % mod;
        if (2 * L > i) continue;
        L = i + 1 - L; B = T; b = d; m = 0;
    }
 
    C.resize(L + 1); C.erase(C.begin());
    for (ll &x : C) x = (mod - x) % mod;
    return C;
}
 
ll linearRec(vector<ll> S, vector<ll> tr, ll k) {
    int n = S.size();
 
    auto combine = [&](vector<ll> a, vector<ll> b) {
        vector<ll> res(n * 2 + 1);
        for(int i = 0; i <= n; ++i) for(int j = 0; j <= n; ++j) 
            res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
        for(int i = 2 * n; i > n; --i) for(int j = 0; j < n; ++j) 
            res[i-1-j]=(res[i-1-j] + res[i] * tr[j]) % mod;
        res.resize(n + 1);
        return res;
    };
 
    vector<ll> pol(n + 1), e(pol);
    pol[0] = e[1] = 1;
 
    for (++k; k; k /= 2) {
        if (k % 2) pol = combine(pol, e);
        e = combine(e, e);
    }
 
    ll res = 0;
    for(int i = 0; i < n; ++i) 
        res = (res + pol[i + 1] * S[i]) % mod;
    return res;
} 