/**********************
 * a[n][m + 1], n equations, m variables. 
 * returns rank of matrix
 * a[][] is changed to reduced row echelon form
 * no solution if a row is like [0, 0, ..., | some non-zero number]
***********************/
typedef long double ld;
const ld eps = 1e-8;
int gauss(vector<vector<ld> > &a) {
	int n = a.size(), m = a[0].size(), r = 0; 
	for(int c = 0; c < m && r < n; c++) {
		int idx = r; 
		for(int i = r + 1; i < n; i++) 
			if(fabsl(a[i][c]) > fabsl(a[idx][c])) idx = i; 
		if(fabsl(a[idx][c]) < eps) continue; 
		a[r].swap(a[idx]); 

		ld t = a[r][c];
		for(int i = c; i < m; i++) a[r][i] /= t;
		for(int i = 0; i < n; i++) if(i != r) {
			ld t = a[i][c];
			for(int j = c; j < m; j++)  
				a[i][j] -= a[r][j] * t;
		}
		r++;
	} return r; 
	// Writing some checkers may be needed.
}


