
const int mod = 1e9 + 7;
struct Mat{
    int a[10][10], d;
    Mat(int _d = 0) { 
        d = _d; 
        memset(a, 0, sizeof a);
    }
    void setIdentity() {
        for(int i = 0; i < d; i++) 
            for(int j = 0; j < d; j++) 
                a[i][j] = (i == j);
    }
    Mat operator *(const Mat &p) const {
        Mat ret(d); int i, j, k;
        ll y = (ll)mod * mod, x;  
        for(i = 0; i < d; i++) {
            for(j = 0; j < d; j++) {
                for(k = x = 0; k < d; k++) {
                    x += (ll)a[i][k] * p.a[k][j];
                    if(x >= y) x -= y;
                } ret.a[i][j] = x % mod;
            }
        } return ret;
    }
    Mat pow(ll n) {
        Mat ret = Mat(d); ret.setIdentity();
        Mat b = *this; 
        for(; n; n >>= 1, b = b * b) 
            if(n & 1) ret = ret * b;
        return ret; 
    }
};