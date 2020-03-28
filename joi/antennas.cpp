#include <bits/stdc++.h>
using namespace std;
//#define int ll
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

const int MAXN = 200005;
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f3f3f3f3f;

int n, q;
int h[MAXN], a[MAXN], b[MAXN];
int ans[MAXN];
vector<pii> qry[MAXN];

int seg[MAXN*4], mn[MAXN*4], tag[MAXN*4];

int get (int o) {
    return seg[o];
}

int getMx (int o) {
    return tag[o];
}


void upd (int o) {
    seg[o] = max(seg[o], tag[o] + mn[o]);
}

void pull (int o) {
    mn[o] = max(mn[o<<1], mn[o<<1|1]);
    seg[o] = max({seg[o], seg[o<<1], seg[o<<1|1]});
    upd(o);
}

void push (int o) {
    if (tag[o] != -INF) {
        tag[o<<1] = max(tag[o<<1], tag[o]);
        tag[o<<1|1] = max(tag[o<<1|1], tag[o]);
        upd(o<<1);
        upd(o<<1|1);
        tag[o] = -INF;
        pull(o);
    }
}

void build () {
    REP (i, MAXN*4) {
        seg[i] = -INF;
        mn[i] = -INF;
        tag[i] = -INF;
    }
}

void segC (int x, int val, int o, int nL, int nR) {
    if (x >= nR || x < nL) {
        return;
    } else if (nL == x && x + 1 == nR) {
        mn[o] = val;
        tag[o] = -INF;
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        segC(x, val, o<<1, nL, nM);
        segC(x, val, o<<1|1, nM, nR);
        pull(o);
    }
}

void segM (int qL, int qR, int val, int o, int nL, int nR) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] = max(tag[o], val);
        upd(o);
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        segM(qL, qR, val, o<<1, nL, nM);
        segM(qL, qR, val, o<<1|1, nM, nR);
        pull(o);
    }
}


int segQ (int qL, int qR, int o, int nL, int nR) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return -INF;
    } else if (qL <= nL && nR <= qR) {
        return get(o);
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        return max(segQ(qL, qR, o<<1, nL, nM),\
            segQ(qL, qR, o<<1|1, nM, nR));
    }
}


vector<pii> opr[MAXN];
void solve () {
    build();
    for (int i=1; i<=n; i++) {
        opr[i].clear();
    }

    for (int i=1; i<=n; i++) {
        if (i+a[i]<=n) {
            opr[i+a[i]].eb(i, 1);
        }
        if (i+b[i]+1<=n) {
            opr[i+b[i]+1].eb(i, -1);
        }
    }

    for (int i=1; i<=n; i++) {
        debug(i);
        for (auto v : opr[i]) {
            if (v.Y > 0) {
                debug("ADD", v.X, -h[v.X]);
                segC(v.X, -h[v.X], 1, 1, n+1);
            } else {
                debug("RMV", v.X, -h[v.X]);
                segC(v.X, -INF, 1,1,n+1);
            }
        }

        int L = i - b[i];
        int R = i - a[i];

        debug(L, R, h[i]);
        segM(L, R+1, h[i], 1, 1, n+1);
        for (auto p : qry[i]) {
            int res = segQ(p.X, i+1, 1, 1, n+1);
            debug(p.Y, p.X, i, res);
            ans[p.Y] = max(ans[p.Y], segQ(p.X, i+1, 1, 1, n+1));
        }
        debug(mn[1], tag[1], seg[1]);

    }

}
/*********************GoodLuck***********************/
signed main () {
    IOS();

    cin >> n;
    for (int i=1; i<=n; i++) {
        cin >> h[i] >> a[i] >> b[i];
    }
    cin >> q;
    for (int i=0; i<q; i++) {
        int l, r;
        cin >> l >> r;
        qry[r].eb(l, i);
    }

    fill(ans,ans+q, -INF);
    solve();
    for (int i=1; i<=n; i++) {
        h[i] = -h[i];
    }
    solve();


    for (int i=0; i<q; i++) {
        cout << (ans[i] < 0 ? -1 : ans[i]) << endl;
    }
}
/*
6
60 4 4
21 3 3
73 3 3
62 1 2
30 4 4
31 1 4
1
2 5
*/
