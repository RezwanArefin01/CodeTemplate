struct Hash {
	struct base {
		string s; int b, mod; 
		vector<int> hash, p; 
		void init(string &_s, int _b, int _mod) { // b > 26, prime. 
			s = _s; b = _b, mod = _mod;
			hash.resize(s.size());
			p.resize(s.size()); 
			hash[0] = s[0] - 'A' + 1; p[0] = 1;
			for(int i = 1; i < s.size(); ++i) {
				hash[i] = (ll) hash[i - 1] * b % mod; 
				hash[i] += s[i] - 'A' + 1;  
				if(hash[i] >= mod) hash[i] -= mod;
				p[i] = (ll) p[i - 1] * b % mod;
			} 
		}
		int get(int l, int r) {
			int ret = hash[r]; 
			if(l) ret -= (ll) hash[l - 1] * p[r - l + 1] % mod;
			if(ret < 0) ret += mod;
			return ret;
		}
	} h[2];
	void init(string &s) {
		h[0].init(s, 29, 1e9+7); 
		h[1].init(s, 31, 1e9+9); 
	}
	pair<int, int> get(int l, int r) {
		return { h[0].get(l, r), h[1].get(l, r) }; 
	}
} H;