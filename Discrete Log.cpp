// Finds minimum x such that a^x = b (mod m) 
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
 
