const int maxn = 3e5+10;
struct node {
    node *ch[2];
    node() { ch[0] = ch[1] = NULL; }
    node *clone() {
        node *ret = new node(); 
        if(this) { 
            ret -> ch[0] = ch[0];
            ret -> ch[1] = ch[1];
        } return ret;
    }
}; 
node *trie[maxn];

void insert(int v, int p, int val) {
    node *curr = trie[v] = trie[p] -> clone();
    for(int i=31; i>=0; i--) {
        int bit = (val >> i) & 1;
        node* &ch = curr -> ch[bit];
        curr = ch = ch -> clone();
    }
}
int queryMin(node *curr, int val) {
    int ans = 0;
    for(int i=31; i>=0; i--) {
        int bit = (val >> i)&1; 
        if(curr -> ch[bit]) {
            curr = curr -> ch[bit];
        } else {
            curr = curr -> ch[bit^1];
            ans |= (1 << i);
        }
    } return ans;
}
int queryMax(node *curr, int val) {
    int ans = 0;
    for(int i=31; i>=0; i--) {
        int bit = (val >> i)&1; 
        if(curr -> ch[bit^1]) {
            ans |= (1<<i);
            curr = curr -> ch[bit^1];
        } else curr = curr -> ch[bit];
    } return ans;
}  
void print(node *curr, stack<int> &st) {
    if(curr -> ch[0] == NULL && curr -> ch[1] == NULL){
        stack<int> tmp = st;
        vector<int> v;
        while(!st.empty()) {    
            v.push_back(st.top());
            st.pop();
        } st = tmp;
        for(int i=v.size()-1; i>=0; i--) 
            cout<<v[i]; 
        cout<<endl;
        return;
    } 
    if(curr -> ch[0]) {
        st.push(0);
        print(curr -> ch[0], st);
        st.pop();
    }
    if(curr -> ch[1]) {
        st.push(1);
        print(curr -> ch[1], st);
        st.pop();
    }
} 
