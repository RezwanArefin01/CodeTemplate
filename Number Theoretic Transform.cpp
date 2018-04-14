const int N = 1 << 18, mod = 7 * 17 * (1 << 23) + 1, g = 3;
int rev[N], w[N], inv_n;

void prepare(int &n) { 
	int sz = 31 - __builtin_clz(n); sz = abs(sz);
	int r = Pow(g, (mod - 1) / n); 
	inv_n = Pow(n, mod - 2);
	w[0] = w[n] = 1; 
	for(int i = 1; i < n; ++i) w[i] = (ll)w[i - 1] * r % mod;
	for(int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1));
}
void ntt(int *a, int n, int dir) { 
	for(int i = 1; i < n - 1; ++i) 
		if(i < rev[i]) swap(a[i], a[rev[i]]);
	for(int m = 2; m <= n; m <<= 1) {
		for(int i = 0; i < n; i += m) {
			for(int j = 0; j < (m >> 1); ++j) {
				int &u = a[i + j], &v = a[i + j + (m >> 1)]; 
				int t = (ll)v * w[dir ? n - n / m * j : n / m * j] % mod;
				v = u - t < 0 ? u - t + mod : u - t;
			 	u = u + t >= mod ? u + t - mod : u + t;
			}
		}
	} if(dir) for(int i = 0; i < n; ++i) a[i] = (ll)a[i] * inv_n % mod;
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