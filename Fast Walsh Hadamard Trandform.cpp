/****************************
Hadamard Matrix - 
1. For XOR-Convolution - 
H = H_inverse = {{1, 1}, {1, -1}} 

2.For AND-Convolution - 
H         = {{0, 1}, {1, 1}} 
H_inverse = {{-1, 1}, {1, 0}}

3. For OR-Convolution - 
H         = {{1, 1}, {1, 0}} 
H_inverse = {{0, 1}, {1, -1}}
***************************/
const int mod = 1e9 + 7;
void fwht(int *p, int n) {
	for(int len = 1; 2 * len <= n; len <<= 1) {
		for(int i = 0; i < n; i += 2 * len) {
			for(int j = 0; j < len; j++) {
				int a = p[i + j];
				int b = p[i + j + len];
				p[i + j] = (a + b) % mod;
				p[i + j + len] = (mod + a - b) % mod;
			}  
		}
	}
}
