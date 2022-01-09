ll mul64(ll a, ll b, ll m) { // 64-bit long long multiplication
	a %= m, b %= m;
	ll ret = 0;
	for(; b; b >>= 1) {
		if(b & 1) ret = (ret + a) % m;
		a = (a + a) % m;
	} return ret;
}
ll Pow(int a, ll p, ll mod) { /* -_- */ }
bool miller_rabin(ll n, ll b) {
	ll m = n - 1, cnt = 0;
	while (m % 2 == 0) m >>= 1, ++cnt;
	ll ret = Pow(b, m, n);
	if (ret == 1 || ret == n - 1) return true;
	while (cnt > 0) {
		ret = mul64(ret, ret, n);
		if (ret == n - 1) return true;
		--cnt;
	} return false;
}
bool ptest(ll n) { // miller-rabin primality test
  	if(n < 2) return false;
  	if(n < 4) return true;
  	const int BASIC[12] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
  	for(int i = 0; i < 12 && BASIC[i] < n; ++i) 
  		if(!miller_rabin(n, BASIC[i])) return false;
  	return true;
}
 
