template<class T, size_t N> struct lazyarray {
    T a[N];
    int vis[N], iter; 
    lazyarray () {
        memset(vis, 0, sizeof vis); 
        iter = 1;
    }
    void clear() { ++iter; }
    T &operator [] (int i) {
        if(vis[i] == iter) {
            return a[i];
        } else {
            vis[i] = iter; 
            return a[i] = 0; 
        } 
    }
};