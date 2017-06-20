/*------Non-Dynamic Convex Hull Trick--------*\ 
Requirements: 
If we want to keep lower envelop then- 
    m[i] > m[i+1], i.e. m[] should be decreasing
In upper envelop case m[] should be increasing
The b[] don't need any ordering.

For query if we want +O(n) complexity then always 
 	x[i] <= x[i+1], i.e. increasing. 
If not then we may need to replace vector with deque (TODO)
If query isn't even monotonic then we can just do Binary Search. Then O(lg n) per query. 
/*-------------------------------------------*/
struct CHT{
	vector<ll> m, b;
	int ptr = 0; 
	bool bad(int l1, int l2, int l3) {
		return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  <= 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]);
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

