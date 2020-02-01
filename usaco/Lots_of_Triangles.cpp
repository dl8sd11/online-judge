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

const int MAXN = 302;
const ll MOD = 1000000007;

struct Point {
    int x, y;
} pt[MAXN];
Point operator - (const Point &p1, const Point &p2) {
    return Point{p1.x-p2.x, p1.y-p2.y};
}
ll cross (const Point &p1, const Point &p2) {
    return ll(p1.x)*p2.y-ll(p1.y)*p2.x;
}
istream& operator >> (istream &is, Point &p) {
    return is >> p.x >> p.y;
}
ostream& operator << (ostream &os, const Point &p) {
    return os << p.x << ' ' << p.y;
}

int n, ans[MAXN], sd[MAXN][MAXN][MAXN];
bool crs[MAXN][MAXN][MAXN];

struct AngleCompare {
    int origin;
    bool operator () (const int &lhs, const int &rhs) const {
        return crs[rhs][origin][lhs];
    }
};

int id[MAXN];
void solve (int f, int t) {
    int idcnt = 0;

    REP (i, n) {
        if (crs[i][f][t]) {
            id[idcnt++] = i;
        }
    }
    int hf = n - idcnt - 2;
    AngleCompare acmp;

    acmp.origin = f;
    sort(id, id+idcnt, acmp);
    REP (i, idcnt) {
        sd[f][t][id[i]] += i + hf;
        sd[t][f][id[i]] += i + hf;
    }

    acmp.origin = t;
    sort(id, id+idcnt, acmp);
    REP (i, idcnt) {
        sd[f][t][id[i]] += idcnt - i - 1 + hf;
        sd[t][f][id[i]] += idcnt - i - 1 + hf;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    #ifndef tmd
    freopen("triangles.in","r",stdin);
    freopen("triangles.out","w",stdout);
    #endif
    cin >> n;
    REP (i, n) {
        cin >> pt[i];
    }

    REP (i, n) {
        REP (j, n) {
            REP (k, n) {
                crs[i][j][k] = cross(pt[k]-pt[j],pt[i]-pt[j]) > 0;
            }
        }
    }

    REP (f, n) {
        REP (t, n) {
            if (f != t) {
                solve(f, t);
            }
        }
    }

    REP (i, n) {
        REP (j, i) {
            REP (k, j) {
                int cur = sd[i][j][k] + sd[i][k][j] + sd[j][k][i];
                cur -= (n-3) * 4;
                cur /= 2;
                ans[cur]++;
            }
        }
    }

    REP (i, n-2) {
        cout << ans[i] << endl;
    }
}
