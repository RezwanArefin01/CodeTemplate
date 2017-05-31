typedef long long ll;
struct point{ 
	int x, y;
	bool operator < (const point &p) const {
		return x == p.x ? y < p.y : x < p.x;
	}
};
ll cross (point a, point b, point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
vector<point> ConvexHull(vector<point>&p, int n) {
	int sz = 0;
	vector<point> hull(n + n);
	sort(p.begin(), p.end());
  	for(int i = 0; i < n; ++i) {
		while (sz > 1 and cross(hull[sz - 2], hull[sz - 1], p[i]) <= 0) --sz;
		hull[sz++] = p[i];
	}
	for(int i = n - 2, j = sz + 1; i >= 0; --i) {
		while (sz >= j and cross(hull[sz - 2], hull[sz - 1], p[i]) <= 0) --sz;
		hull[sz++] = p[i];
	}
	hull.resize(sz - 1);
	return hull;
}	