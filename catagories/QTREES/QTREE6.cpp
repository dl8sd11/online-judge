#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const int MAXLG = __lg(MAXN) + 2;
const ll MOD = 1000000007;

int n, q;
vector<int> edge[MAXN];

struct BIT {
    int bit[MAXN];
    void add (int x, int val) {
        for (x+=2; x<MAXN; x+=-x&x) {
            bit[x] += val;
        }
    }

    int qry (int x) {
        int ret = 0;
        for (x+=2; x>0; x-=-x&x) {
            ret += bit[x];
        }
        return ret;
    }

    void rngA (int l, int r, int val) {
        add(l, val);
        add(r+1, -val);
    }

    int rngQ (int l, int r) {
        return qry(r) - qry(l-1);
    }
} dp[2], cnt[2];

int sz[MAXN], hd[MAXN], in[MAXN], pa[MAXN], dep[MAXN];
int anc[MAXLG][MAXN];

void dfsSz (int nd, int par) {
    sz[nd] = 1;
    dep[nd] = dep[par] + 1;
    pa[nd] = par;
    anc[0][nd] = par;

    for (int &v : edge[nd]) {
        if (v != par) {
            dfsSz(v, nd);
            sz[nd] += sz[v];
             if (edge[nd][0] == par || sz[v] > sz[edge[nd][0]]) {
                swap(v, edge[nd][0]);
             }
        }
    }
}

int tms = 1;
void dfsHd (int nd, int par) {
    in[nd] = tms++;
    for (auto v : edge[nd]) {
        if (v != par) {
            hd[v] = (v == edge[nd][0]) ? hd[nd] : v;
            dfsHd(v, nd);
        }
    }
}

bool white[MAXN];

int kth (int nd, int k) {
    for (int i=0; i<MAXLG; i++) {
        if (k>>i & 1) {
            nd = anc[i][nd];
        }
    }
    return nd;
}

int getTop (int nd, int color) {
    int h = hd[nd];

    int tmp = cnt[color].rngQ(in[h], in[nd]);
    debug(color);
    debug(nd, h, tmp, dep[nd]-dep[h]+1);

    if (cnt[color].rngQ(in[h], in[nd]) == dep[nd] - dep[h] + 1) {
        return getTop(pa[h], color);
    } else {
        int L = dep[h], R = dep[nd] + 1;
        while (L < R - 1) {
            int M = (L + R) >> 1;
            int mid = kth(nd, dep[nd] - M);
            if (cnt[color].rngQ(in[mid], in[nd]) == dep[nd] - M + 1) {
                R = M;
            } else {
                L = M;
            }
        }
        debug(L);
        return kth(nd, dep[nd]-L);
    }
}

int nodeQry (int nd, int color) {
    return dp[color].qry(in[nd]);
}

void pathUpd (int from, int to, int val, int color) {
    if (dep[hd[to]] <= dep[from]) {
        debug(from, to, in[from], in[to], val);
        dp[color].rngA(in[from], in[to], val);
    } else {
        debug(from, to, in[from], in[to], val);
        dp[color].rngA(in[hd[to]], in[to], val);
        pathUpd(from, pa[hd[to]], val, color);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfsSz(1, 0);
    hd[1] = 0;
    dfsHd(1, 0);

    for (int i=1; i<=n; i++) {
        dp[0].rngA(in[i], in[i], sz[i]-1);
        cnt[0].add(in[i], 1);
    }

    for (int i=1; i<MAXLG; i++) {
        for (int j=1; j<=n; j++) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }

    cin >> q;
    while (q--) {
        int cmd, nd;
        cin >> cmd >> nd;

        int p = pa[nd];

        debug(cmd, nd);

        if (cmd == 0) {

            int tp = getTop(p, white[nd]);
            debug(tp);
            tp = kth(nd, dep[nd]-dep[tp]-1);
            debug(nd, tp, dep[tp], dep[nd]);
            cout << nodeQry(tp, white[nd]) + 1<< endl;
        } else {

            debug(in[nd], white[nd]);
            cnt[white[nd]].add(in[nd], -1);
            white[nd] ^= 1;
            cnt[white[nd]].add(in[nd], 1);
            int cur[2];

            REP (i, 2) {
                cur[i] = nodeQry(nd, i) + 1;
            }

            REP (i, 2) {
                int tp = getTop(p, i);
                int dl = (white[nd] == i) ? cur[i] : -cur[i];
                debug(tp, p, dl, i);
                pathUpd(tp, p, white[nd] == i ? cur[i] : -cur[i], i);
            }
        }
    }
}
/*

5
2 1
3 2
4 2
5 4
5
1 1
0 5
1 4
0 5
0 1

*/
