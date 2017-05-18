// O(n)
typedef long long ll;
ll histro(vector<ll> &hist) {
	stack<int> st; int n = hist.size(),i=0; ll Max=0;
	while(i <= n) { 
		ll h = (i == n?0:hist[i]);
		if(st.empty() || h >= hist[st.top()]) 
			st.push(i++);
		else {
			int tp = st.top(); st.pop();
			Max = max(Max, hist[tp]*(st.empty()? i : i-1-st.top()));
		}
	} return Max;
}