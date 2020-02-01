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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int r, c, n;
struct Point {
    int x, y, id;
    int getEid () const {
        if (x == 0) {
            return 0;
        } else if (y == c) {
            return 1;
        } else if (x == r) {
            return 2;
        } else {
            return 3;
        }
    }

    bool operator < (const Point &p) {
        int eid = getEid();
        if (eid != p.getEid()) {
            return eid < p.getEid();
        } else {
            if (eid == 0) {
                return y < p.y;
            } else if (eid == 1) {
                return x < p.x;
            } else if (eid == 2) {
                return y > p.y;
            } else {
                return x > p.x;
            }
        }
    }
};

typedef pair<int, int> pii;
vector<Point> pt;
int prv[MAXN], nxt[MAXN];

pii del (int L) {
    int R = nxt[L];
    int LL = prv[L];
    int RR = nxt[R];
    nxt[LL] = RR;
    prv[RR] = LL;
    if (pt[LL].id == pt[RR].id) {
        return pii(LL, RR);
    } else {
        return pii(-1, -1);
    }
}

bool edge (int x, int y) {
    return x == 0 || x == r || y == 0 || y == c;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> r >> c >> n;
    REP (i, n) {
        int xf, yf, xs, ys;
        cin >> xf >> yf >> xs >> ys;
        if (edge(xf, yf) && edge(xs, ys)) {
            pt.push_back({xf, yf, i});
            pt.push_back({xs, ys, i});
        }
    }

    sort(pt.begin(), pt.end());

    REP (i, SZ(pt)) {
        nxt[i] = (i+1) % SZ(pt);
        prv[i] = (i-1+SZ(pt)) % SZ(pt);
        debug(pt[i].x, pt[i].y, pt[i].id);
    }

    queue<int> bfs;
    REP (i, SZ(pt)) {
        if (pt[i].id == pt[nxt[i]].id) {
            bfs.emplace(i);
        }
    }

    int cnt = 0;
    while (!bfs.empty()) {
        if (cnt == SZ(pt)/2) {
            break;
        }
        int cur = bfs.front();
        bfs.pop();

        pii ret = del(cur);
        if (ret.first != -1) {
            bfs.emplace(ret.first);
        }
        cnt++;
    }

    if (cnt == SZ(pt)/2) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
