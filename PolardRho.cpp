inline ll mul64(ll x, ll y, ll mod) {
  ll ans = 0;
  __asm__ (
    "movq %1,%%rax\n imulq %2\n idivq %3\n"
    :"=d"(ans):"m"(x),"m"(y),"m"(mod):"%rax"
  );
  return ans;
}
inline ll Pow(ll a, ll p, ll mod) {
  ll ret = 1; while(p) {
    if(p & 1) ret = mul64(ret, a, mod); 
    a = mul64(a, a, mod); 
    p >>= 1;
  } return ret;
}
bool miller_rabin(ll n, ll b) {
  ll m = n - 1, cnt = 0;
  while (m % 2 == 0) m >>= 1, ++cnt;
  ll ret = Pow(b, m, n);
  if (ret == 1 || ret == n - 1) return true;
  while (cnt > 0) {
    ret = mul64(ret, ret, n);
    if (ret == n - 1) return true;
    --cnt;
  } return false;
}
bool ptest(ll n) { // miller-rabin primality test
    if(n < 2) return false;
    if(n < 4) return true;
    const int BASIC[12] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
    for(int i = 0; i < 12 && BASIC[i] < n; ++i) 
      if(!miller_rabin(n, BASIC[i])) return false;
    return true;
}
ll pollard_rho(ll n, ll seed) { 
  ll x, y;
  x = y = rand() % (n - 1) + 1;
  int head = 1, tail = 2;
  while (true) {
    x = mul64(x, x, n);
    x = (x + seed) % n;
    if (x == y) return n;
    ll d = __gcd(max(x - y, y - x), n);
    if (1 < d && d < n) return d;
    if (++head == tail) y = x, tail <<= 1;
  }
}
void factorize(ll n, vector<ll> &divisor) { 
  if (n == 1) return;
  if (ptest(n)) divisor.push_back(n);
  else {
    ll d = n;
    while (d >= n) d = pollard_rho(n, rand()%(n-1)+1);
    factorize(n / d, divisor);
    factorize(d, divisor);
  }
}
vector<ll> divisors(vector<ll> d) {
  vector<ll> ret = {1};
  sort(d.begin(), d.end());
  for (int i = 0, count = 1; i < d.size(); ++i) {
    if (i + 1 == d.size() || d[i] != d[i + 1]) {
      int c = ret.size();
      ret.resize(ret.size() * (count+1));
      ll n = 1;
      for (int j = 1; j <= count + 1; ++j) {
        for (int k = 0; k < c; ++k) {
          ret[(j-1)*c+k] = ret[k]*n;
        }
        n *= d[i];
      }
      count = 1;
    } else count += 1;
  }
  sort(ret.begin(), ret.end());
  return ret;
}
