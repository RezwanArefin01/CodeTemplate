typedef long long ll; 

struct maxxor {
	ll best[64], msb;
	maxxor() { memset(best, -1, sizeof best); }
	void add(ll x) {
		while(x > 0) {
			msb = 63 - __builtin_clzll(x); 
			if(best[msb] == -1) {
				best[msb] = x; break;
			} else x ^= best[msb]; 
		}
	}
	ll get() {
		ll ret = 0;
		for(int i = 63; i >= 0; i--) {
			if(best[i] != -1) 
				ret = max(ret, ret ^ best[i]);
		} return ret;
	}
} ds;