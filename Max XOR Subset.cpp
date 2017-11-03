 
struct maxxor {
	int best[32], msb;
	maxxor() { memset(best, -1, sizeof best); }
	void add(int x) { 
		while(x > 0) {
			msb = 31 - __builtin_clz(x); // clzll for ll
			if(best[msb] == -1) {
				best[msb] = x; break;
			} else x = x ^ best[msb]; 
		}
	}
	int get(int ret = 0) {
		for(int i = 31; i >= 0; i--) {
			if(best[i] != -1) 
				ret = max(ret, ret ^ best[i]);
		} return ret;
	}
} ds;
