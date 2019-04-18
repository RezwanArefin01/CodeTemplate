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

