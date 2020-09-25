int largestRectangleArea(vector<int>& h) {
  h.push_back(0); 
  int ret = 0; 
  stack<int> st;
  
  for(int i = 0; i < h.size(); ++i) {
    while(st.size() && h[st.top()] >= h[i]) {
      int t = st.top(); st.pop(); 
      ret = max(ret, h[t] * (st.size() ? i - st.top() - 1: i)); 
    }
    st.push(i);
  }
  
  return ret;
}