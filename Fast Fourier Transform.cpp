typedef long double ld;
typedef complex<ld> Complex;
typedef valarray<Complex> ValComplex; 

const ld PI = 2 * acos(0.0); 

void fft(ValComplex &p, bool inverse = 0) {
	int n = p.size(); 
	if(n <= 1) return;
	
	ValComplex f = p[slice(0, n/2, 2)], 
			   g = p[slice(1, n/2, 2)];
	
	fft(f, inverse); fft(g, inverse); 
	
	Complex omega_n = exp(Complex(0, 2 * PI / n)), w = 1;
	if(inverse) omega_n = Complex(1, 0) / omega_n; 

	for(int k = 0; k < n / 2; k++) {
		Complex add = w * g[k];
		p[k]       = f[k] + add;
		p[k + n/2] = f[k] - add;
		w *= omega_n;
	}
}

void ifft(ValComplex& x) {
    fft(x, 1);
    x /= x.size();
}

vector<int> multiply(vector<int> &a, vector<int> &b) {
	int n = a.size(), m = b.size(), t = n + m - 1, sz = 1;
	while(sz < t) sz <<= 1;

	ValComplex x(sz), y(sz), z(sz);
	for(int i = 0; i < n; i++) x[i] = Complex(a[i], 0);
	for(int i = n; i < sz; i++) x[i] = Complex(0, 0);

	for(int i = 0; i < m; i++) y[i] = Complex(b[i], 0);
	for(int i = m; i < sz; i++) y[i] = Complex(0, 0);

	fft(x); fft(y);
	for(int i = 0; i < sz; i++) z[i] = x[i] * y[i]; 

	ifft(z); 
	vector<int> res(sz); 
	for(int i = 0; i < sz; i++) res[i] = z[i].real() + 0.5;
	while(res.size() > 1 && res.back() == 0) res.pop_back(); 
	return res; 
}