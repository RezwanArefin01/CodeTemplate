// Sieve 

const int N = 2e5 + 10; 
bitset<N> mark;
vector<int> prime; 

void sieve() { mark.set(); // Linear Sieve
	for(int i = 2; i < N; i++) {
		if(mark[i]) prime.push_back(i); 
		for(int j = 0; j < prime.size() && i * prime[j] < N; j++) {
			mark[i * prime[j]] = 0; 
			if(i % prime[j] == 0) break;
		}
	}
}


// Binomial 

const int mod = 1e9 + 7; 

int fact[N], inv[N]; 
inline int Pow(int a, int p) {
	int ret = 1; while(p) {
		if(p & 1) ret = (ll) ret * a % mod;
		a = (ll) a * a % mod;
		p >>= 1;
	} return ret;
}
void init() {
	fact[0] = 1; 
	for(int i = 1; i < N; ++i)
		fact[i] = (ll) fact[i - 1] * i % mod; 
	inv[N - 1] = Pow(fact[N - 1], mod - 2); 
	for(int i = N - 2; i >= 0; --i) 
		inv[i] = (ll) inv[i + 1] * (i + 1) % mod; 
}
int C(int n, int r) {
	int ret = (ll) fact[n] * inv[n - r] % mod; 
	return (ll) ret * inv[r] % mod; 
}



// Discrete Log
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


