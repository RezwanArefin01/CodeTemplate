const int N = 1e5 + 10; 

#define next asdfg

char s[N]; 
int SA[N], iSA[N]; 
int cnt[N], next[N]; 
bool bh[N], b2h[N]; 
int lcp[N]; 

void buildSA(int n) {
    for(int i = 0; i < n; i++) SA[i] = i; 
    sort(SA, SA + n, [](int i, int j) { return s[i] < s[j]; }); 

    for(int i = 0; i < n; i++) {
        bh[i] = i == 0 || s[SA[i]] != s[SA[i - 1]]; 
        b2h[i] = 0; 
    }

    for(int h = 1; h < n; h <<= 1) {
        int tot = 0;
        for(int i = 0, j; i < n; i = j) {
            j = i + 1; 
            while(j < n && !bh[j]) j++; 
            next[i] = j; tot++; 
        } if(tot == n) break; 

        for(int i = 0; i < n; i = next[i]) {
            for(int j = i; j < next[i]; j++) 
                iSA[SA[j]] = i; 
            cnt[i] = 0; 
        }
        
        cnt[iSA[n - h]]++; 
        b2h[iSA[n - h]] = 1; 
        for(int i = 0; i < n; i = next[i]) {
            for(int j = i; j < next[i]; j++) {
                int s = SA[j] - h; 
                if(s < 0) continue; 
                int head = iSA[s]; 
                iSA[s] = head + cnt[head]++; 
                b2h[iSA[s]] = 1; 
            }
            for(int j = i; j < next[i]; j++) {
                int s = SA[j] - h;
                if(s < 0 || !b2h[iSA[s]]) continue; 
                for(int k = iSA[s] + 1; !bh[k] && b2h[k]; k++) 
                    b2h[k] = 0; 
            }
        }
        for(int i = 0; i < n; i++) {
            SA[iSA[i]] = i; 
            bh[i] |= b2h[i]; 
        }
    }
    for(int i = 0; i < n; i++) iSA[SA[i]] = i; 
}

void buildLCP(int n) {
    for(int i = 0, k = 0; i < n; i++) {
        if(iSA[i] == n - 1) { k = 0; continue; }
        int j = SA[iSA[i] + 1]; 
        while(i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
        lcp[iSA[i]] = k;
        if(k) k--;
    }
}
