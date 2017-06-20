//Non-Dynamic Convex Hull Trick
struct CHT{
	vector<ll> m, b;
	int ptr = 0; 
	bool bad(int l1, int l2, int l3) {
		return (b[l3] - b[l1]) * (m[l1] - m[l2])  < (b[l2] - b[l1]) * (m[l1] - m[l3]);
		//For upper envelop use <= sign
	} 

	void add(ll _m, ll _b) { 
		//Requiremens (for lower envelop) 
		//   m[i] >= m[i+1], i.e decreasing 
		//if we are keeping upper envelop then - 
		//   m[i] <= m[i+1], i.e increasing 
		m.push_back(_m);
		b.push_back(_b); 
		int s = m.size(); 
		while(s >= 3 && bad(s-3, s-2, s-1)) {
			s--; 
			m.erase(m.end()-2);
			b.erase(b.end()-2); 
		}
	}  
	ll f(int i, ll x) { return m[i]*x + b[i]; }

	ll query(ll x) {   
		// Requirement 
		//   if x[i] =< x[i+1], ie. increasing, then poiner walk will do
		//   else we need to BS the solution 
		if(ptr >= m.size()) ptr = m.size()-1;
		while(ptr < m.size()-1 && 
			f(ptr+1, x) < f(ptr, x)) ptr++; 
			//If finding upper envelop then use >= sign
		return f(ptr, x); 
	}
}; 

