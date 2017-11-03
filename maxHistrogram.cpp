ll histro(vector<ll> &hist) {
	stack<int> st; ll Max = 0;
	for(int i = 0; i <= hist.size(); i++) { 
		ll h = (i == n ? 0 : hist[i]);
		if(st.empty() || h >= hist[st.top()]) 
			st.push(i++);
		else {
			int tp = st.top(); st.pop();
			Max = max(Max, hist[tp] * (st.empty() ? i : i - 1 - st.top()));
		}
	} return Max;
} 
