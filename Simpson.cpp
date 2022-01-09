double f(double x) { return x * x; }

double simpson(double a, double b, double eps,
              double whole, double fa, double fb, 
              double fm, int rec) {
  double m   = (a + b)/2,  h   = (b - a)/2;
  double lm  = (a + m)/2,  rm  = (m + b)/2;
  // serious numerical trouble: it won't converge
  if ((eps/2 == eps) || (a == lm)) { 
    errno = EDOM; return whole; 
  }

  double flm = f(lm),      frm = f(rm);
  double left  = (h/6) * (fa + 4*flm + fm);
  double right = (h/6) * (fm + 4*frm + fb);
  double delta = left + right - whole;

  // depth limit too shallow
  if (rec <= 0 && errno != EDOM) errno = ERANGE;

  if (rec <= 0 || fabs(delta) <= 15*eps)
    return left + right + (delta)/15;
  return simpson(f,a,m,eps/2, left,fa,fm,flm,rec-1) +
         simpson(f,m,b,eps/2,right,fm,fb,frm,rec-1);
}

double integrate(double a, double b, double eps) {   
  errno = 0;
  double h = b - a;
  if (h == 0) return 0;
  double fa = f(a), fb = f(b), fm = f((a + b)/2);
  double S = (h/6)*(fa + 4*fm + fb);
  return simson(a, b, eps, S, fa, fb, fm, 20);
}