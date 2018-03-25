ll mod = 25 * (1 << 22) + 1; 
ll g = 3, w[1 << 22]; // g = primitive root(mod)

void ntt(vector<ll> &p, bool inv = 0) {
	int n = p.size(), i = 0;
	for(int j = 1; j < n - 1; ++j) {
		for(int k = n >> 1; k > (i ^= k); k >>= 1);
		if(j < i) swap(p[i], p[j]);
	}
	ll r = Pow(g, (mod - 1) / n);
	if(inv) r = Pow(r, mod - 2);
	
	w[0] = 1; 
	for(int i = 1; i <= n; i++) 
		w[i] = w[i - 1] * r % mod; 

	for(int l = 1, m; (m = l << 1) <= n; l <<= 1) {
		for(int i = 0; i < n; i += m) {
			for(int j = i, add = n / m, z = 0; j < i + l; ++j, z += add) {
				ll t = p[j + l] * w[z] % mod;
				p[j + l] = p[j] - t + mod; p[j] += t;
				if(p[j + l] >= mod) p[j + l] -= mod;
				if(p[j] >= mod) p[j] -= mod;
			}
		}
	} if(inv) {
		ll t = Pow(n, mod - 2);
		for(int i = 0; i < n; i++) 
			p[i] = p[i] * t % mod;
	} 
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
			if(fpow(root, (p - 1) / factor[i], p) == 1) {
				flag = false;	
				break;
			}
		}
		if (flag) return root;
	}
}