const int N = 1e5 + 5;
string s;
int sa[N], pos[N], lcp[N], tmp[N], gap, n;

bool cmp_sa(int a, int b) {
	if(pos[a] - pos[b])
		return pos[a] < pos[b];
	a += gap; b += gap;
	return (a < n && b < n) ? pos[a] < pos[b] : a > b;
}

void build_sa() {
	n = s.size();
	for(int i = 0; i < n; i++)
		sa[i] = i, pos[i] = s[i];
	for(gap = 1; ; gap <<= 1) {
		sort(sa, sa + n, cmp_sa);
		for(int i = 1; i < n; i++) tmp[i] = tmp[i-1] + cmp_sa(sa[i-1], sa[i]);
		for(int i = 0; i < n; i++) pos[sa[i]] = tmp[i];
		if(tmp[n-1] == n-1) break;
	}
}
void build_lcp() {
	for(int i = 0, k = 0; i < n; i++) if(pos[i] - n + 1) {
		for(int j = sa[pos[i] + 1]; s[j + k] == s[i + k]; k++);
		lcp[pos[i]] = k;
		if(k) k--;
	}
}


/// ALT 

struct SuffixArray {
	const int L;
	string s;
	vector<vector<int> > P;
	vector<pair<pair<int,int>,int> > M;

	SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L) {
		for(int i = 0; i < L; i++) P[0][i] = int(s[i]);
		for(int skip = 1, level = 1; skip < L; skip *= 2, level++) {
			P.push_back(vector<int>(L, 0));
			for (int i = 0; i < L; i++) 
				M[i] = {{P[level-1][i], i + skip < L ? P[level-1][i + skip] : -1000}, i};
			sort(M.begin(), M.end());
      		for(int i = 0; i < L; i++)
      			P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
		}    
	}

	vector<int> GetSuffixArray() { return P.back(); }

	// returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
	int LongestCommonPrefix(int i, int j) {
		int len = 0;
		if(i == j) return L - i;
		for(int k = P.size() - 1; k >= 0 && i < L && j < L; k--) {
			if (P[k][i] == P[k][j]) {
				i += 1 << k;
				j += 1 << k;
				len += 1 << k;
			}
		} return len;
  	}
};
