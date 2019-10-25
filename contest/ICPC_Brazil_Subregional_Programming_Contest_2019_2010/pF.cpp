#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 100005;

struct PP {
    int x1, y1, x2, y2;
} ter;
int n, p;
vector<PP> seg;

struct Query {
    int l, r, val;
};
vector<Query> qry[MAXN];

ll dt[MAXN*4], tag[MAXN*4];


ll Get (int o=1, int l=0, int r=MAXN) {
    return tag[o] ? r - l : dt[o];
}

void pull (int o, int l, int r) {
    int mid = (l + r) >> 1;
    dt[o] = Get(o<<1, l, mid) + Get(o<<1|1, mid, r);
}

void add (int qL, int qR, int val, int o=1, int nL=0, int nR=MAXN) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] += val;
    } else {
        int mid = (nL + nR) >> 1;
        add(qL, qR, val, o<<1, nL, mid);
        add(qL, qR, val, o<<1|1, mid, nR);
        pull(o, nL, nR);
    }
}

ll solve (int rd) {
    memset(dt, 0, sizeof(dt));
    memset(tag, 0, sizeof(tag));

    for (auto pp : seg) {
        PP cur = {pp.x1-rd, pp.y1-rd, pp.x2+rd, pp.y2+rd};
        cur.x1 = max(cur.x1, ter.x1);
        cur.y1 = max(cur.y1, ter.y1);
        cur.x2 = min(cur.x2, ter.x2);
        cur.y2 = min(cur.y2, ter.y2);

        qry[cur.x1].push_back({cur.y1, cur.y2, 1});
        qry[cur.x2].push_back({cur.y1, cur.y2, -1});
    }

    ll ans = 0;
    REP (i, MAXN) {
        for (auto Q : qry[i]) {
            debug(Q.l, Q.r, Q.val);
            add(Q.l, Q.r, Q.val);
        }
        ans += Get();
    }

    REP (i, MAXN) {
        qry[i].clear();
    }
    return ans;
}
/****GOOD_LUCK****/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        seg.push_back({a, b, c, d});
    }
    cin >> p;
    {
        int q, w, e, r;
        cin >> q >> w >> e >> r;
        ter = {q, w, e, r};
    }

    int l = 0, r = 1000006;
    ll area = (ter.x2 - ter.x1) * ll(ter.y2 - ter.y1);
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        ll res = solve(mid);
        debug(mid, res);
        if (res >= (area * p + 99) / 100) {
            r = mid;
        } else {
            l = mid;
        }
    }

    cout << r << endl;

    return 0;
}
