/*------Non-Dynamic Convex Hull Trick--------*\ 
Requirements: 
If m[] is decreasing: 
	If we want minimums then bad(s-3, s-2, s-1), x[] increasing
	If we want maximums then bad(s-1, s-2, s-3), x[] decreasing 

If m[] is increasing: 	
	If we want maximums then bad(s-3, s-2, s-1), x[] increasing 
	If we want minimums then bad(s-1, s-2, s-3), x[] decreasing 
	
If x isn't monotonic, then do Ternary Search or keep intersections and do binary search
/*-------------------------------------------*/
struct CHT{
	vector<ll> m, b;
	int ptr = 0; 
	bool bad(int l1, int l2, int l3) { // returns intersect(l1, l3) <= intersect(l1, l2)
		return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2]) <= 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]);
	} 

	void add(ll _m, ll _b) { 
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
		if(ptr >= m.size()) ptr = m.size()-1;
		while(ptr < m.size()-1 && 
			f(ptr+1, x) < f(ptr, x)) ptr++; 
		return f(ptr, x); 
	}
}; 

