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
const double INF = 1000006;
const double eps = 1e-9;

typedef pair<double, double> pdd;

istream& operator >> (istream& is, pdd &pt) {
    return is >> pt.first >> pt.second;
}
ostream& operator << (ostream& os, const pdd &pt) {
    return os << pt.first << ' ' << pt.second;
}

pdd operator - (const pdd &p1, const pdd &p2) {
    return pdd{p1.first-p2.first, p1.second-p2.second};
}
double cross (const pdd &p1, const pdd &p2) {
    return p1.first*p2.second-p1.second*p2.first;
}
double cross (const pdd &p1, const pdd &p2, const pdd &p3) {
    return cross(p3-p2, p1-p2);
}

vector<pdd> build_convex (vector<pdd> &pts) {
    sort(pts.begin(), pts.end());
    vector<pdd> hull;
    hull.reserve(pts.size()+1);
    REP (phase, 2) {
        auto start = hull.size();
        for (const auto &p : pts) {
            while (hull.size()>=start+2&&cross(hull[hull.size()-2],hull.back(), p)>=0) {
                hull.pop_back();
            }
            hull.emplace_back(p);
        }
        hull.pop_back();
        reverse(pts.begin(), pts.end());
    }
    if (hull.size()==2&&hull[1]==hull[0]) {
        hull.pop_back();
    } else if (hull.empty()) {
        hull.emplace_back(pts.front());
    }
    return hull;
}

double norm (const pdd &p) {
    return sqrt(p.first*p.first+p.second*p.second);
}
double dis (const pdd &p1, const pdd &p2) {
    return norm(p1-p2);
}

int nxt (int c, int s) {
    return c+1>=s?c+1-s:c+1;
}

double bridge (const vector<pdd> &xhull, const vector<pdd> &yhull) {
    double ans = 0;

    int szx = static_cast<int>(xhull.size());
    int szy = static_cast<int>(yhull.size());
    int mx = 0, mn = 0;
    double mxv = -INF, mnv = INF;
    pdd init = xhull[1] - xhull[0];
    REP (i, szy) {
        double cur = cross(init, yhull[i]-xhull[0]);
        if (cur > mxv) {
            mxv = cur;
            mx = i;
        }
        if (cur < mnv) {
            mnv = cur;
            mn = i;
        }
    }

    REP (i, szx) {
        int ni = nxt(i, szx);
        pdd cur = xhull[ni] - xhull[i];
        while (cross(cur,yhull[mx]-xhull[i]) < cross(cur,yhull[nxt(mx,szy)]-xhull[i])) {
            mx = nxt(mx, szy);
        }
        while (cross(cur,yhull[mn]-xhull[i]) > cross(cur,yhull[nxt(mn,szy)]-xhull[i])) {
            mn = nxt(mn, szy);
        }

        if (cross(cur,yhull[mn]-xhull[i])*cross(cur,yhull[mx]-xhull[i])>0) {
            if (szx == 2 || cross(cur,yhull[mn]-xhull[i])*cross(cur,xhull[nxt(ni,szx)]-xhull[i])<0) {
                ans = max(ans, cross(cur,yhull[mn]-xhull[i])/norm(cur));
            }
        }
    }

    return ans;
}

int n, m;
/*********************GoodLuck***********************/
int main () {
    IOS();

    while (cin >> n >> m && n && m) {
        vector<pdd> px(n), py(m);
        REP (i, n) {
            cin >> px[i];
        }
        REP (i, m) {
            cin >> py[i];
        }

        vector<pdd> xhull = build_convex(px), yhull = build_convex(py);
        double ans = 0;

        if (xhull.size() <= yhull.size()) {
            swap(xhull, yhull);
        }

        if (xhull.size() == 1) {
            ans = dis(xhull.front(), yhull.front());
        } else {

        }

        if (ans > eps) {
            cout << fixed << setprecision(3) << ans << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }

    }

}
/*
not complete
*/
