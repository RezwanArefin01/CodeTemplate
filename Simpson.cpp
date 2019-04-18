const double eps = 1e-4;  

double f(double x) { return .5 * x; }

double simpson(double a, double b) {
	return (f(a) + 4 * f((a + b) / 2) + f(b)) * (b - a) / 6;
}

double integrate(double l, double r, double e, double S) {
	double m = (l + r) / 2; 
	double left = simpson(l, m), right = simpson(m, r); 
	double T = left + right;
	if(fabs(T - S) <= 15 * e || r - l < 1e-10) 
		return T + (T - S) / 15; 
	return integrate(l, m, e / 2, left) + integrate(m, r, e / 2, right);
}

double integrate(double l, double r) { 
	return integrate(l, r, eps, simpson(l, r)); 
}