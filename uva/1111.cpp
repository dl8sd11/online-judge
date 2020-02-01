#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmdd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 500005;
const ll MOD = 1000000007;

typedef pair<int,int> point;

int n;
istream& operator >> (istream &is, point &p) {
    return is >> p.first >> p.second;
}
ostream& operator << (ostream &os, point &p) {
    return os << p.first << " " << p.second;
}
point operator - (const point &p1, const point &p2) {
    return point{p1.first - p2.first, p1.second - p2.second};
}
int operator * (const point &p1, const point &p2) {
    return p1.first * p2.second - p1.second * p2.first;
}
int ori (const point &p1, const point &p2, const point &p3) {
    return (p3-p2)*(p1-p2);
}

vector<point> build_convex_hull (vector<point> pts) {
    sort(pts.begin(), pts.end());
    vector<point> hull;
    hull.reserve(pts.size() + 1);
    REP (phase, 2) {
        auto start = hull.size();
        for (const auto &p : pts) {
            while (hull.size()>=start+2 && ori(hull[hull.size()-2],hull.back(), p) >= 0) {
                hull.pop_back();
            }
            hull.emplace_back(p);
        }
        hull.pop_back();
        reverse(pts.begin(), pts.end());
    }

    #ifdef tmdd
    for (auto P : hull) {
        debug(P);
    }
    #endif
    return hull;
}

int nxt (int c, int s) {
    return c+1 >= s ? c+1-s : c+1;
}

double dis (point a, point b) {
    point dt = a - b;
    return sqrt(dt.first*dt.first+dt.second*dt.second);
}

double min_width (const vector<point> &hull) {
    double res = 1000006;
    int sz = static_cast<int>(hull.size());
    int j = 1;
    REP (i, sz) {
        point cur = hull[nxt(i,sz)] - hull[i];
        while ((hull[j]-hull[i])*cur < (hull[nxt(j,sz)]-hull[i])*cur) {
            j = nxt(j, sz);
        }
        debug(i, j,(hull[j]-hull[i])*cur,dis(hull[i], hull[nxt(i,sz)]));
        res = min(res,(hull[j]-hull[i])*cur/dis(hull[i], hull[nxt(i,sz)]));
    }
    return res;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    int tcnt = 0;
    while (cin >> n && n) {
        vector<point> pts(n);
        REP (i, n) {
            cin >> pts[i];
        }

        vector<point> hull = build_convex_hull(pts);
        cout << "Case " << ++tcnt << ": ";
        cout << fixed << setprecision(2) << ceil(min_width(hull)*100)/100 << endl;
    }
}

/*
3
0 0
3 0
0 4
4
0 10
10 0
20 10
10 20
0

*/
