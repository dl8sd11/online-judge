#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
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


typedef pair<int,int> pii;
int n;

istream& operator >> (istream &is, pii &p) {
    return is >> p.first >> p.second;
}
ostream& operator << (ostream &os, const pii&p) {
    return os << p.first << ' ' << p.second;
}

pii operator - (const pii &p1, const pii &p2) {
    return pii{p1.first-p2.first, p1.second-p2.second};
}
int cross (const pii &p1, const pii &p2) {
    return p1.first*p2.second - p1.second*p2.first;
}
int cross (const pii &p1, const pii &p2, const pii &p3) {
    return cross(p3-p2, p1-p2);
}
int cross (int p1, int p2, int p3, const vector<pii> &hull) {
    return cross(hull[p1], hull[p2], hull[p3]);
}
int dot (const pii &p1, const pii &p2) {
    return p1.first*p2.first + p1.second*p2.second;
}
int dot (const pii &p1, const pii &p2, const pii &p3) {
    return dot(p3-p2, p1-p2);
}
int dot (int p1, int p2, int p3, const vector<pii> &hull) {
    return dot(hull[p1], hull[p2], hull[p3]);
}

vector<pii> build_convex (vector<pii> pts) {
    vector<pii> hull;
    sort(pts.begin(), pts.end());
    hull.reserve(pts.size() + 1);
    REP (phase, 2) {
        auto start = hull.size();
        for (const auto &p : pts) {
            while (hull.size()>=start+2&&cross(hull[hull.size()-2],hull.back(),p)>=0) {
                hull.pop_back();
            }
            hull.emplace_back(p);
        }
        hull.pop_back();
        reverse(pts.begin(), pts.end());
    }

#ifdef tmd
    for (auto p : hull) {
        debug(p);
    }
#endif
    return hull;
}

inline int nxt (int c, int s) {
    return c+1>=s?c+1-s:c+1;
}

double dis (const pii &p1, const pii &p2) {
    pii dl = p1 - p2;
    return sqrt(dl.first*dl.first+dl.second*dl.second);
}

double rect_cover (const vector<pii> &hull) {
    double res = 1000006;
    int sz = static_cast<int>(hull.size());
    int u = 1, l = 1, r = 1;
    REP (i, sz) {
        if (dot(hull[i], hull[0], hull[1]) < dot(hull[r], hull[0], hull[1])) {
            r = i;
        }
    }

    REP (d, sz) {
        int nd = nxt(d, sz);
        while (cross(nd, d, u, hull) < cross(nd, d, nxt(u, sz), hull)) {
            u = nxt(u, sz);
        }
        while (dot(nd, d, l, hull) < dot(nd, d, nxt(l, sz), hull)) {
            l = nxt(l, sz);
        }
        while (dot(nd, d, r, hull) > dot(nd, d, nxt(r, sz), hull)) {
            r = nxt(r, sz);
        }

        double len = dis(hull[nd], hull[d]);
        double s1 = cross(nd, d, u, hull) / len;

        double s2 = dot(hull[nd]-hull[d], hull[l]-hull[r]) / len;

        debug(d, u, l, r, s1, s2);

        res = min(res, (s1 + s2) * 2);
    }

    return res;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    while (cin >> n) {
        vector<pii> pts(n);
        REP (i, n) {
            cin >> pts[i];
        }

        vector<pii> hull = build_convex(pts);
        cout << fixed << setprecision(10) << rect_cover(hull) << endl;
    }
}
