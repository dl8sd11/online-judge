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

const int MAXN = 100005;
const ll MOD = 1000000007;

struct Point {
    int x, y;
};

int operator ^ (const Point &cur, const Point &oth) {
    return cur.x*oth.y-cur.y*oth.x;
}

bool operator < (const Point &q, const Point &p) {
    int h1 = q.y == 0 ? q.x < 0 : q.y < 0;
    int h2 = p.y == 0 ? p.x < 0 : p.y < 0;
    if (h1 != h2) {
        return h1 < h2;
    } else {
        return (q^p) > 0;
    }
}

istream& operator >> (istream& is, Point &pt) {
    return is >> pt.x >> pt.y;
}
ostream& operator << (ostream& os, Point &pt) {
    return os << pt.x << " " << pt.y;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    int n;
    cin >> n;
    vector<Point> pts(n*2);
    REP (i, n) {
        cin >> pts[i];
    }
    sort(pts.begin(), pts.begin()+n); // sort by angle
    copy_n(pts.begin(), n, pts.begin()+n);

    int j = 0, sx = 0, sy = 0;

    ll ans = 0;
    for (int i=0; i<n; i++) {
        j = i, sx = 0, sy = 0;
        while (j < i+n ) { // && (pts[i]^pts[j]) >= 0
            sx += pts[j].x;
            sy += pts[j].y;
            ans = max(ans, ll(sx)*sx+ll(sy)*sy);
            j++;
        }


        sx -= pts[i].x;
        sy -= pts[i].y;
    }

    cout << ans << endl;
}

/*
2
1 1
-1 1
*/
