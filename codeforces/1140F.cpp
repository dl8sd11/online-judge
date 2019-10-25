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

typedef pair<int,int> pii;

const int MAXN = 600015;
const int MAXC = 300003;
const ll MOD = 1000000007;

struct Log {
    int u, v;
    ll szux, szuy, szvx, szvy, ans;
};
vector<Log> logs;

int djs[MAXN], q;
ll ans, res[MAXN], szx[MAXN], szy[MAXN];
map<pii, int> lst;


int fnd (int x) {
    return x == djs[x] ? x : fnd(djs[x]);
}

void uni (int x, int y) {
    x = fnd(x);
    y = fnd(y);
    logs.push_back({x, y, szx[x], szy[x], szx[y], szy[y], ans});
    if (x != y) {
        if (szx[x] + szy[x] > szx[y] + szy[y]) {
            swap(x, y);
        }
        djs[x] = y;
        ans -= szx[x] * szy[x] + szx[y] * szy[y];
        szx[y] += szx[x];
        szy[y] += szy[x];
        ans += szx[y] * szy[y];
    }
}

void undo () {
    assert(!logs.empty());
    Log cur = logs.back();
    logs.pop_back();
    ans = cur.ans;
    djs[cur.u] = cur.u;
    djs[cur.v] = cur.v;
    szx[cur.u] = cur.szux;
    szy[cur.u] = cur.szuy;
    szx[cur.v] = cur.szvx;
    szy[cur.v] = cur.szvy;
}

vector<pii> seg[MAXN*4];
void add_query (pii cur, int qL, int qR, int v=1, int nL=0, int nR=q) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        seg[v].emplace_back(cur);
        debug(cur.first, cur.second, nL, nR);
    } else {
        int nM = (nL + nR) >> 1;
        add_query(cur, qL, qR, v<<1, nL, nM);
        add_query(cur, qL, qR, v<<1|1, nM, nR);
    }
}

void time_dfs (int v=1, int l=0, int r=q) {
    for (auto p : seg[v]) {
        uni(p.first, p.second);
    }

    if (l == r - 1) {
        res[l] = ans;
    } else {
        int m = (l + r) >> 1;
        time_dfs(v<<1, l, m);
        time_dfs(v<<1|1, m, r);
    }

    REP (i, SZ(seg[v])) {
        undo();
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    REP1 (i, MAXC) {
        djs[i] = i;
        djs[i+MAXC] = i+MAXC;
        szx[i] = 1;
        szy[i+MAXC] = 1;
    }

    cin >> q;
    REP (i, q) {
        int x, y;
        cin >> x >> y;
        y += MAXC;
        if (lst.count({x, y})) {
            add_query({x, y}, lst[{x,y}], i);
            lst.erase({x, y});
        } else {
            lst[{x,y}] = i;
        }
    }
    for (auto p : lst) {
        add_query(p.first, p.second, q);
    }
    time_dfs();

    REP (i, q) {
        cout << res[i] << " \n"[i==q-1];
    }
    return 0;
}
