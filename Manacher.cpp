// l[2 * i] = len of palindrome centered at s[i]
// l[2*i+1] = len of palindrome centered at s[i], s[i+1]
vector<int> manacher(string &s) {
	int n = s.size(); vector<int> l(2 * n); 
	for (int i = 0, j = 0, k; i < n * 2; i += k, j = max(j - k, 0)) {
		while (i >= j && i + j + 1 < n * 2 && s[(i - j) / 2] == s[(i + j + 1) / 2]) ++j;
		l[i] = j;
		for (k = 1; i >= k && j >= k && l[i - k] != j - k; ++k) 
			l[i + k] = min(l[i - k], j - k);
	} return l;
}