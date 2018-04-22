const int maxn = 2e5 + 10; 
bitset<maxn> mark;
vector<int> prime; 

void sieve() { mark.set(); // Linear Sieve
	for(int i = 2; i < maxn; i++) {
		if(mark[i]) prime.push_back(i); 
		for(int j = 0; j < prime.size() && i * prime[j] < maxn; j++) {
			mark[i * prime[j]] = 0; 
			if(i % prime[j] == 0) break;
		}
	}
}

