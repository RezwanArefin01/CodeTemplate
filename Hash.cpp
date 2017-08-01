struct Hash{
	ll h[5010][2], pow[5010][2], n, 
	   b[2] = {(ll)1e9+9, (ll)1e9+7}, 
	   mod[2] = {(ll)1e9+7, (ll)1e9+9}; 

	Hash(){}
	void init(string &str) {
		n = str.size() - 1; 	
		pow[0][0] = pow[0][1] = 1; 
		h[0][0] = h[0][1] = 0;

		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < 2; j++) {
				pow[i][j] = pow[i-1][j] * b[j] % mod[j]; 
				h[i][j] = (h[i-1][j] * b[j] + str[i] - 'a' + 1) % mod[j];
			} 
		}	
	}

	pair<ll, ll> hash(int l, int r) {
		ll ret[2]; 
		for(int i = 0; i < 2; i++) {
			ret[i] = (h[r][i] - (h[l-1][i]*pow[r-l+1][i] % mod[i]) + mod[i]) % mod[i]; 
		}
		return pair<ll,ll>(ret[0], ret[1]);
	}
};
Hash h, rh; 

inline void init(string str) {
	h.init(str); 
	reverse(str.begin(), str.end());
	str.pop_back(); 
	str = "#" + str;
	rh.init(str);
}
inline bool ispal(int l, int r) {
	int n = h.n;
	auto x = h.hash(l, r); 
	auto y = rh.hash(n-r+1, n-l+1);
	return x == y;
}
 
