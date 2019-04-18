
const int maxn = 1e5 + 10;
string s, t; 
int pi[maxn]; 

void prefixFn() {
	int now = pi[0] = -1; 
	for(int i = 1; i < s.size(); i++) {
		while(now != -1 && s[now + 1] != s[i]) now = pi[now]; 
		if(s[now + 1] == s[i]) pi[i] = ++now;
		else pi[i] = now = -1; 
	}
}

int kmp() {
	prefixFn(); 
	int cnt = 0, now = -1;
	for(int i = 0; i < t.size(); i++) {
		while(now != -1 && s[now + 1] != t[i]) now = pi[now];
		if(s[now + 1] == t[i]) ++now;
		else now = -1;
		if(now == s.size() - 1) { now = pi[now]; cnt++; }
	} return cnt; 
}