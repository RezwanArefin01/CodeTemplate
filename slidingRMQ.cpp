//O(n)
vector<int> slidingRMQ(vector<int> &arr, int k) {
	vector<int> ret(arr.size(), 1e9); // ret[i] = minimum of arr[i, i+k-1]
	deque<int> Q;
	for(int i=0; i<arr.size(); i++) {
		while(!Q.empty() && Q.back() > arr[i])
			Q.pop_back();
		Q.push_back(arr[i]);
		if(i >= k && arr[i-k] == Q.front())
			Q.pop_front();
		if(i >= k-1) ret[i-k+1] = Q.front();
	} return ret;
}