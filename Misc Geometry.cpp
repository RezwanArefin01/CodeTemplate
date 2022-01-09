///usr/bin/g++ -O2 $0 -o ${0%.cpp} && echo "----------" && ./${0%.cpp}; exit;
#include <bits/stdc++.h>
using namespace std;

typedef double T;
struct pt {
  T x,y;
  pt(T x=0, T y=0): x(x), y(y) {}
  pt operator+(pt p) { return {x+p.x, y+p.y}; }
  pt operator-(pt p) { return {x-p.x, y-p.y}; }
  pt operator*(T d) { return {x*d, y*d}; }
  pt operator/(T d) { return {x/d, y/d}; } 
};

bool operator==(pt a,pt b){return a.x==b.x&&a.y==b.y;}
bool operator!=(pt a, pt b) { return !(a == b); }

ostream& operator<<(ostream& os, pt p) {
  return os << "("<< p.x << "," << p.y << ")";
}

T sq(pt p) { return p.x*p.x + p.y*p.y; }
double abs(pt p) { return sqrt(sq(p)); }

T dot(pt v, pt w) { return v.x*w.x + v.y*w.y; }
T cross(pt v, pt w) { return v.x*w.y - v.y*w.x; }

template <typename T> int sgn(T x) {
  return (T(0) < x) - (x < T(0));
}
pt scale(pt c, double a, pt p) { return c + (p-c)*a; }

pt rot(pt p, double a) {
  return {p.x*cos(a) - p.y*sin(a), 
          p.x*sin(a) + p.y*cos(a)};
}

pt perp(pt p) { return {-p.y, p.x}; }

// transform r, ifp->fp, q->fq
pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) {
  pt pq = q-p, num{cross(pq, fq-fp), dot(pq, fq-fp)};
  return fp + pt{cross(r-p, num), dot(r-p, num)} / sq(pq);
}

bool isPerp(pt v, pt w) {return dot(v,w) == 0;}

// angle between v and w, in [0, pi]
double angle(pt v, pt w) {
  double cosTheta = dot(v,w) / abs(v) / abs(w);
  return acos(max(-1.0, min(1.0, cosTheta)));
}

// +ve ifc is left to a->b, -ve forright, else 0
T orient(pt a, pt b, pt c) { return cross(b-a,c-a); }

// ifp is inside smaller angle formed by ab and ac
bool inAngle(pt a, pt b, pt c, pt p) {
  assert(orient(a,b,c) != 0);
  if(orient(a,b,c) < 0) swap(b,c);
  return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}

// oriented angle between a->b and a->c
double orientedAngle(pt a, pt b, pt c) {
  T ang = angle(b - a, c - a); 
  if(orient(a, b, c) < 0) ang = 2*M_PI - ang; 
  return ang; 
}

bool isConvex(vector<pt> p) {
  bool hasPos = 0, hasNeg = 0;
  for(int i = 0, n = p.size(); i < n; i++) {
    int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
    hasPos |= o > 0; 
    hasNeg |= o < 0;
  }
  return !(hasPos && hasNeg);
}

// polar Sort
bool half(pt p) { // true ifabove x axis
  assert(p.x != 0 || p.y != 0); 
  return p.y > 0 || (p.y == 0 && p.x < 0);
}
bool half2(pt p, pt v) { // keep direction v first
  return cross(v,p)<0||(cross(v,p)==0&&dot(v,p)<0);
}
void polarSort(vector<pt> &v) {
  sort(v.begin(), v.end(), [](pt v, pt w) {
    return make_tuple(half(v), 0) <
           make_tuple(half(w), cross(v,w));
  });
  // subtract p forsorting around point p
  // add sq(v) in tuple forbreaking ties
}


struct line {
  pt v; T c;
  // from direction vector v and offset c
  line(pt v, T c) : v(v), c(c) {}
  // from equation ax+by=c
  line(T a, T b, T c) : v({b,-a}), c(c) {}
  // from points P and Q
  line(pt p, pt q) : v(q-p), c(cross(v,p)) {}
  
  T side(pt p) { return cross(v,p)-c; }

  double dist(pt p) { return abs(side(p)) / abs(v); }
  double sqDist(pt p) {
    return side(p)*side(p) / (double)sq(v);
  }

  line perpThrough(pt p) { return {p, p + perp(v)}; }

  // sorting points (projection) along a line
  bool cmpProj(pt p, pt q) {
    return dot(v,p) < dot(v,q);
  }

  line translate(pt t) { return {v, c + cross(v,t)}; }
  line shiftLeft(double dist) {
    return {v, c + dist * abs(v)};
  }

  pt proj(pt p) {return p - perp(v)*side(p)/sq(v);}
  pt refl(pt p) {return p - perp(v)*2*side(p)/sq(v);}
};

// intersection of two lines
bool inter(line l1, line l2, pt &out) {
  T d = cross(l1.v, l2.v);
  if(d == 0) return false;
  out = (l2.v*l1.c - l1.v*l2.c) / d; 
  return true;
}

// angle bisector of two lines
line bisector(line l1, line l2, bool interior) {
  assert(cross(l1.v, l2.v) != 0); 
  double sign = interior ? 1 : -1;
  return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign,
          l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
}

// check ifp lies in disk of diameter ab
bool inDisk(pt a, pt b, pt p) {
  return dot(a - p, b - p) <= 0;
}

bool onSegment(pt a, pt b, pt p) {
  return orient(a,b,p) == 0 && inDisk(a,b,p);
}

// segment intersection 
// proper intersection = 1 point, not endpoints
bool properInter(pt a, pt b, pt c, pt d, pt &out) {
  double oa = orient(c,d,a),
         ob = orient(c,d,b),
         oc = orient(a,b,c),
         od = orient(a,b,d);
  if(oa*ob < 0 && oc*od < 0) {
    out = (a*ob - b*oa) / (ob-oa);
    return true;
  }
  return false;
}
// all intersections
struct cmpX {
  bool operator()(pt a, pt b) {
    return make_pair(a.x, a.y) < make_pair(b.x, b.y);
  }
};
set<pt,cmpX> inters(pt a, pt b, pt c, pt d) {
  pt out;
  if(properInter(a,b,c,d,out)) return {out};
  set<pt,cmpX> s;
  if(onSegment(c,d,a)) s.insert(a);
  if(onSegment(c,d,b)) s.insert(b);
  if(onSegment(a,b,c)) s.insert(c);
  if(onSegment(a,b,d)) s.insert(d);
  return s;
}

// segment point distance
double segPoint(pt a, pt b, pt p) {
  if(a != b) {
    line l(a,b);
    if(l.cmpProj(a,p) && l.cmpProj(p,b)) 
      return l.dist(p); 
  }
  return min(abs(p-a), abs(p-b));
}

// segment segment distance
double segSeg(pt a, pt b, pt c, pt d) {
  pt dummy;
  if(properInter(a,b,c,d,dummy))
    return 0;
  return min({segPoint(a,b,c), segPoint(a,b,d),
              segPoint(c,d,a), segPoint(c,d,b)});
}

double areaTriangle(pt a, pt b, pt c) {
  return abs(cross(b-a, c-a)) / 2.0;
}

double areaPolygon(vector<pt> p) {
  double area = 0.0;
  for(int i = 0, n = p.size(); i < n; i++) 
    area += cross(p[i], p[(i+1)%n]); 
  return abs(area) / 2.0;
}

// point in polygon: ray test 
// check if[PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) {
  return ((q.y>=a.y)-(p.y>=a.y)) * orient(a,p,q) > 0;
}
// ifstrict, returns false when A is on the boundary
bool inPolygon(vector<pt> p, pt a, bool strict=true) {
  int numCrossings = 0;
  for(int i = 0, n = p.size(); i < n; i++) {
    if(onSegment(p[i], p[(i+1)%n], a))
      return !strict;
    numCrossings += crossesRay(a, p[i], p[(i+1)%n]);
  }
  return numCrossings & 1; 
}

// amplitude travelled around point A, from P to Q
double angleTravelled(pt a, pt p, pt q) {
  double ampli = angle(p-a, q-a);
  if(orient(a,p,q) > 0) return ampli;
  else return -ampli;
}

// winding number (number of full turns around point)
// WARNING: not defined ifa is on boundary of poly
int windingNumber(vector<pt> p, pt a) {
  double ampli = 0;
  for(int i = 0, n = p.size(); i < n; i++)
    ampli += angleTravelled(a, p[i], p[(i+1)%n]);
  return round(ampli / (2*M_PI));
}

// circle stuff 
pt circumCenter(pt a, pt b, pt c) {
  b = b-a, c = c-a; 
  assert(cross(b,c) != 0);
  return a + perp(b*sq(c) - c*sq(b))/cross(b,c)/2;
}

// circle line intersection. returns # intersections 
int circleLine(pt o, double r, line l, 
               pair<pt,pt> &out) {
  double h2 = r*r - l.sqDist(o);
  if(h2 >= 0) {
    pt p = l.proj(o); 
    pt h = l.v*sqrt(h2)/abs(l.v); 
    out = {p-h, p+h};
  }
  return 1 + sgn(h2);
}

// circle circle intersection. returns # intersections
int circleCircle(pt o1, double r1, pt o2, double r2, 
                 pair<pt,pt> &out) {
  pt d = o2 - o1; double d2 = sq(d);
  if(d2 == 0) { assert(r1 != r2); return 0; } 
  double pd = (d2 + r1*r1 - r2*r2)/2; 
  double h2 = r1*r1 - pd*pd/d2;
  if(h2 >= 0) {
    pt p = o1 + d*pd/d2, h = perp(d)*sqrt(h2/d2);
    out = {p-h, p+h};
  }
  return 1 + sgn(h2);
}

// tangets of two circles 
int tangents(pt o1, double r1, pt o2, double r2, 
              bool inner, vector<pair<pt,pt>> &out) {
  if(inner) r2 = -r2;
  pt d = o2-o1;
  double dr = r1-r2, d2 = sq(d), h2 = d2-dr*dr;
  if(d2 == 0 || h2 < 0) { assert(h2 != 0); return 0; }
  for(double sign : {-1,1}) {
    pt v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
    out.push_back({o1 + v*r1, o2 + v*r2});
  }
  return 1 + (h2 > 0);
}



struct p3 {
  T x,y,z;
  p3 operator+(p3 p) { return {x+p.x, y+p.y, z+p.z}; }
  p3 operator-(p3 p) { return {x-p.x, y-p.y, z-p.z}; }
  p3 operator*(T d) { return {x*d, y*d, z*d}; }
  p3 operator/(T d) { return {x/d, y/d, z/d}; } 

  bool operator==(p3 p) {
    return tie(x,y,z) == tie(p.x,p.y,p.z);
  }
  bool operator!=(p3 p) { return !operator==(p); }
};

p3 zero{0,0,0};


// dot product 
T operator|(p3 v, p3 w) {
  return v.x*w.x + v.y*w.y + v.z*w.z;
}

// cross product 
p3 operator*(p3 v, p3 w) {
  return {v.y*w.z - v.z*w.y,
          v.z*w.x - v.x*w.z,
          v.x*w.y - v.y*w.x};
}

T sq(p3 v) { return v|v; }
double abs(p3 v) { return sqrt(sq(v)); }
p3 unit(p3 v) { return v/abs(v); }

double angle(p3 v, p3 w) {
  double cosTheta = (v|w) / abs(v) / abs(w);
  return acos(max(-1.0, min(1.0, cosTheta)));
}

// positive side is the direction of pq X pr
T orient(p3 p, p3 q, p3 r, p3 s) {
  return (q - p)*(r - p) | (s - p);
}


struct plane {
  p3 n; T d;
  // from normal n and offset d
  plane(p3 n, T d) : n(n), d(d) {}
  // from normal n and point P
  plane(p3 n, p3 p) : n(n), d(n|p) {}
  // from three non-collinear points P,Q,R
  plane(p3 p, p3 q, p3 r) : plane((q-p)*(r-p), p) {}

  // positive side in direction of n
  T side(p3 p) { return (n|p)-d; }
  double dist(p3 p) { return abs(side(p))/abs(n); }
  plane translate(p3 t) { return {n, d+(n|t)}; }
  plane shiftUp(double dist) {
    return {n, d + dist*abs(n)};
  }
  p3 proj(p3 p) {return p - n*side(p)/sq(n);}
  p3 refl(p3 p) {return p - n*2*side(p)/sq(n);}
};

// 3D coords based on plane
struct coords {
  p3 o, dx, dy, dz;
  // from three points P,Q,R on the plane:
  // build an orthonormal 3D basis
  coords(p3 p, p3 q, p3 r) : o(p) {
    dx = unit(q-p);
    dz = unit(dx*(r-p));
    dy = dz*dx;
  }
  // from four points P,Q,R,S:
  // take directions PQ, PR, PS as is
  coords(p3 p, p3 q, p3 r, p3 s) :
      o(p), dx(q-p), dy(r-p), dz(s-p) {}

  pt pos2d(p3 p) {
    return {(p-o)|dx, (p-o)|dy};
  }
  p3 pos3d(p3 p) {
    return {(p-o)|dx, (p-o)|dy, (p-o)|dz};
  }
};

// 3D line
struct line3d {
  p3 d, o;
  // from two points P, Q
  line3d(p3 p, p3 q) : d(q-p), o(p) {}
  // from two planes p1, p2 
  line3d(plane p1, plane p2) {
    d = p1.n*p2.n;
    o = (p2.n*p1.d - p1.n*p2.d)*d/sq(d);
  }
  double sqDist(p3 p) { return sq(d*(p-o))/sq(d); }
  double dist(p3 p) { return sqrt(sqDist(p)); }
  bool cmpProj(p3 p, p3 q) { return (d|p) < (d|q); }
  p3 proj(p3 p) { return o + d*(d|(p-o))/sq(d); }
  p3 refl(p3 p) { return proj(p)*2 - p; }
  p3 inter(plane p) {return o - d*p.side(o)/(p.n|d);}
};

// line line distance 
double dist(line3d l1, line3d l2) {
    p3 n = l1.d*l2.d;
    if(n == zero) // parallel
        return l1.dist(l2.o);
    return abs((l2.o-l1.o)|n)/abs(n);
}

// closest point on L1 from L2
p3 closestOnL1(line3d l1, line3d l2) {
    p3 n2 = l2.d*(l1.d*l2.d);
    return l1.o + l1.d*((l2.o-l1.o)|n2)/(l1.d|n2);
}

line3d perpThrough(plane p, p3 o) {return line3d(o, o+p.n);}
plane perpThrough(line3d l, p3 o) {return plane(l.d, o);}

// angles between planes/lines 
double smallAngle(p3 v, p3 w) { // in [0, pi/2]
    return acos(min(abs(v|w)/abs(v)/abs(w), 1.0));
}
double angle(plane p1, plane p2) {
  return smallAngle(p1.n, p2.n);
}
bool isParallel(plane p1, plane p2) {
  return p1.n*p2.n == zero;
}
bool isPerpendicular(plane p1, plane p2) {
  return (p1.n|p2.n) == 0;
}
double angle(line3d l1, line3d l2) {
  return smallAngle(l1.d, l2.d);
}
bool isParallel(line3d l1, line3d l2) {
  return l1.d*l2.d == zero;
}
bool isPerpendicular(line3d l1, line3d l2) {
  return (l1.d|l2.d) == 0;
}
double angle(plane p, line3d l) {
  return M_PI/2 - smallAngle(p.n, l.d);
}
bool isParallel(plane p, line3d l) {
  return (p.n|l.d) == 0;
}
bool isPerpendicular(plane p, line3d l) {
  return p.n*l.d == zero;
}


// polyhedron
p3 vectorArea2(vector<p3> p) { // area vector
  p3 S = zero;
  for(int i = 0, n = p.size(); i < n; i++)
      S = S + p[i]*p[(i+1)%n];
  return S;
}
double area(vector<p3> p) {
    return abs(vectorArea2(p)) / 2.0;
}

// polyhedron orient faces 
bool operator<(p3 p, p3 q) {
  return tie(p.x, p.y, p.z) < tie(q.x, q.y, q.z);
}
struct edge {
  int v;
  bool same; // is the common edge in the same order?
};

void reorient(vector<vector<p3>> &fs) {
  int n = fs.size();
  
  vector<vector<edge>> g(n);
  map<pair<p3,p3>,int> es;
  for(int u = 0; u < n; u++) {
    for(int i = 0, m = fs[u].size(); i < m; i++) {
      p3 a = fs[u][i], b = fs[u][(i+1)%m];
      if(es.count({a,b})) { 
        int v = es[{a,b}];
        g[u].push_back({v,true});
        g[v].push_back({u,true});
      } else if(es.count({b,a})) { 
        int v = es[{b,a}];
        g[u].push_back({v,false});
        g[v].push_back({u,false});
      } else { 
        es[{a,b}] = u;
      }
    }
  }
  
  vector<bool> vis(n,false), flip(n);
  flip[0] = false;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for(edge e : g[u]) {
      if(!vis[e.v]) {
        vis[e.v] = true;
        flip[e.v] = (flip[u] ^ e.same);
        q.push(e.v);
      }
    }
  }
  
  for(int u = 0; u < n; u++)
    if(flip[u])
      reverse(fs[u].begin(), fs[u].end());
}

double volume(vector<vector<p3>> fs) {
  double vol6 = 0.0;
  for(vector<p3> f : fs)
    vol6 += (vectorArea2(f)|f[0]);
  return abs(vol6) / 6.0;
}


// spherical geometry 
// 3D point from lat, lon 
// lat from y to z, lon from x to y
p3 sph(double r, double lat, double lon) {
  lat *= M_PI/180, lon *= M_PI/180;
  return {r*cos(lat)*cos(lon), 
          r*cos(lat)*sin(lon), 
          r*sin(lat)};
}

// spehere line intersection, returns # intersection
int sphereLine(p3 o, double r, line3d l, 
               pair<p3,p3> &out) {
  double h2 = r*r - l.sqDist(o);
  if(h2 < 0) return 0; 
  p3 p = l.proj(o); 
  p3 h = l.d*sqrt(h2)/abs(l.d); 
  out = {p-h, p+h};
  return 1 + (h2 > 0);
}

// great-circle-distance
double greatCircleDist(p3 o, double r, p3 a, p3 b) {
  return r * angle(a-o, b-o);
}

// spherical segment intersection
bool validSegment(p3 a, p3 b) {
  return a*b != zero || (a|b) > 0;
}
// 1 intersection, not endpoints
bool properInter(p3 a, p3 b, p3 c, p3 d, p3 &out) {
  p3 ab = a*b, cd = c*d; 
  int oa = sgn(cd|a),
      ob = sgn(cd|b),
      oc = sgn(ab|c),
      od = sgn(ab|d);
  out = ab*cd*od; 
  return (oa != ob && oc != od && oa != oc);
}
// check ifp on segment a, b
bool onSphSegment(p3 a, p3 b, p3 p) {
  p3 n = a*b;
  if(n == zero)
      return a*p == zero && (a|p) > 0;
  return (n|p) == 0 && (n|a*p) >= 0 && (n|b*p) <= 0;
}
struct directionSet : vector<p3> {
  using vector::vector; // import constructors
  void insert(p3 p) {
    for(p3 q : *this) if(p*q == zero) return;
    push_back(p);
  }
};
// handles improper intersections 
directionSet intersSph(p3 a, p3 b, p3 c, p3 d) {
  assert(validSegment(a, b) && validSegment(c, d));
  p3 out;
  if(properInter(a, b, c, d, out)) return {out};
  directionSet s;
  if(onSphSegment(c, d, a)) s.insert(a);
  if(onSphSegment(c, d, b)) s.insert(b);
  if(onSphSegment(a, b, c)) s.insert(c);
  if(onSphSegment(a, b, d)) s.insert(d);
  return s;
}

// spherical angle
// angle between plane through ab and ac
double angleSph(p3 a, p3 b, p3 c) {
  return angle(a*b, a*c);
}
double orientedAngleSph(p3 a, p3 b, p3 c) {
  if((a*b|c) >= 0)
    return angleSph(a, b, c);
  else
    return 2*M_PI - angleSph(a, b, c);
}

// area of spherical polygon
double areaOnSphere(double r, vector<p3> p) {
  int n = p.size();
  double sum = -(n-2)*M_PI;
  for(int i = 0; i < n; i++)
    sum += orientedAngleSph(p[(i+1)%n], p[(i+2)%n], p[i]);
  return r*r*sum;
}

// 3D winding number
int windingNumber3D(vector<vector<p3>> fs) {
  double sum = 0;
  for(vector<p3> f : fs)
    sum += remainder(areaOnSphere(1, f), 4*M_PI);
  return round(sum / (4*M_PI));
}



int main() {
  
}