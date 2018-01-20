// Returns first n terms of the inverrse of p.
vector<ll> inverse(vector<ll> p, int n) { 
	vector<ll> h = {Pow(p[0], mod - 2)};
	for(int d = 1; h.size() < n; ++d) {
		vector<ll> pmod(1 << d);
		for(int i = 0; i < (1 << d); ++i) 
			pmod[i] = i < p.size() ? p[i] : 0;
		vector<ll> t = multiply(pmod, h);
		t.resize(1 << d);
		for(int i = 0; i < (1 << d); ++i) 
			if(t[i]) t[i] = mod - t[i];
		t[0] += 2; if(t[0] >= mod) t[0] -= mod;
		h = multiply(t, h);
		h.resize(1 << d);
	} h.resize(n); return h;
}
vector<ll> division(vector<ll> p, vector<ll> q) {
	if(p.size() < q.size()) return {0};
	reverse(p.begin(), p.end());
	reverse(q.begin(), q.end()); 
	int deg = p.size() - q.size() + 1;
	vector<ll> ret = multiply(inverse(q, deg), p);
	ret.resize(deg);
	reverse(ret.begin(), ret.end());
	while(ret.size() && ret.back() == 0) ret.pop_back();
	return ret;
}

vector<ll> reminder(vector<ll> p, vector<ll> q) {
	if(p.size() < q.size()) return p; 
	vector<ll> t = multiply(q, division(p, q)); 
	vector<ll> ans(p.size()); 
	for(int i = 0; i < p.size(); i++) {
		ans[i] = p[i] - t[i];
		if(ans[i] < 0) ans[i] += mod;
	} while(ans.size() && ans.back() == 0) ans.pop_back();
	return ans;
}

