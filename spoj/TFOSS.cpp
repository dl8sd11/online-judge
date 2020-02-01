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

int t, n;
typedef pair<int,int> point;
point operator - (const point &p1, const point &p2) {
    return point{p1.first-p2.first, p1.second-p2.second};
}
ll operator * (const point &p1, const point &p2) {
    return ll(p1.first)*(p2.second) - ll(p1.second)*(p2.first);
}

void make_convex (vector<point> pts, vector<point> &hull) {
    sort(pts.begin(), pts.end());
    REP (way, 2) {
        auto start = hull.size();
        for (const auto &p : pts) {
            while (hull.size() >= start+2 && (p-hull.back())*(hull.back()-hull[hull.size()-2]) >= 0) {
                hull.pop_back();
            }
            hull.emplace_back(p);
        }
        hull.pop_back();
        reverse(pts.begin(), pts.end());
    }
    if (hull.size() == 2 && hull[0] == hull[1]) {
        hull.pop_back();
    }

}

ll dis (const point &p) {
    return ll(p.first)*p.first + ll(p.second)*p.second;
}

int nxt (int c, int s) {
    return c + 1 >= s ? c+1-s : c+1;
}

ll max_distance (vector<point> &hull) {
    ll res = 0;
    if (hull.size() == 2) {
        res = dis(hull[1] - hull[0]);
    } else {
        int idx = 1;
        int sz = static_cast<int>(hull.size());
        REP (i, sz) {
            point cur = hull[nxt(i, sz)]-hull[i];
            while ((hull[idx]-hull[i])*cur > (hull[nxt(idx, sz)]-hull[i])*cur) {
                idx = nxt(idx, sz);
            }
            int nxi = nxt(i, sz), nxj = nxt(idx, sz);
            res = max(res, dis(hull[i]-hull[idx]));
            res = max(res, dis(hull[i]-hull[nxj]));
            res = max(res, dis(hull[nxi]-hull[idx]));
            res = max(res, dis(hull[nxi]-hull[nxj]));
        }
    }
    return res;
}

/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> t;
    while (t--) {
        cin >> n;
        vector<point> pts(n);
        REP (i, n) {
            cin >> pts[i].first >> pts[i].second;
        }
        vector<point> hull;
        make_convex(pts, hull);

        cout << max_distance(hull) << endl;
    }
}
