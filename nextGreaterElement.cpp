// O(n)
vector<int> nextGreaterElement(vector<int> &arr) {
	int n = arr.size(); stack<int> s;
	vector<int> ret(n+1, n); 
	for(int i=n-1; i>=0; i--) {
		while(!s.empty() && arr[s.top()] <= arr[i]) 
			s.pop();
		if(!s.empty()) ret[i] = s.top();
		s.push(i);
	} return ret; 
}