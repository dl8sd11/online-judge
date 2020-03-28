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

const int MAXN = 200005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;

int n, m;
ll x, y;
vector<array<int,3> > rb; // robot

void ckmax (ll &X, ll Y) {
    X = max(X, Y);
}

struct Segment_Tree {
    ll seg[MAXN*2];

    void init () {
        fill(seg,seg+2*m,-INF);
    }

    ll rqry (int l, int r) {
        ll mx = -INF;
        for (l+=m,r+=m;l<r;l>>=1,r>>=1) {
            if (l&1) {
                ckmax(mx, seg[l++]);
            }
            if (r&1) {
                ckmax(mx, seg[--r]);
            }
        }
        return mx;
    }

    void schg (int X, ll v) {
        for (seg[X+=m]=v; X>1; X>>=1) {
            seg[X>>1] = max(seg[X], seg[X^1]);
        }
    }

    void rchg (int l, int r, ll v) {
        for (l+=m,r+=m;l<r;l>>=1,r>>=1) {
            if (l&1) {
                ckmax(seg[l++], v);
            }
            if (r&1) {
                ckmax(seg[--r], v);
            }
        }
    }

    ll sqry (int X) {
        ll ret = -INF;
        for (X+=m; X>0; X>>=1) {
            ckmax(ret, seg[X]);
        }
        return ret;
    }

} dp[3][3];

vector<int> lval;

int rbd (int X) {
    array<int,3> q = {X, -iNF, -iNF};
    return lower_bound(ALL(rb), q)-rb.begin();
}

int lbd (int x) {
    return lower_bound(ALL(lval),x)-lval.begin();
}


ll pd[3][MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> x >> y;
    REP (i, m) {
        int c, l, r;
        cin >> c >> l >> r;
        lval.eb(l);
        c--;
        rb.push_back({r, l, c});
    }

    REP (i, 3) {
        REP (j, 3) {
            dp[i][j].init();
        }
    }

    sort(ALL(rb));
    sort(ALL(lval));

    ll ans = 0, cans = 0;
    REP (i, m) {
        int l, r, c;
        r = rb[i][0];
        l = rb[i][1];
        c = rb[i][2];

        ll cur = (r-l+1)*x;
        ll cc = (r-l+1)*x;

        int L = rbd(l), R = i;
        int lid = lbd(l), rid = lbd(r+1);
        REP (v, 3) {
            ckmax(cur, dp[v][0].rqry(0,L) + (r-l+1)*x);
            debug(v);
            debug(dp[v][0].rqry(0,L) + (r-l+1)*x);
            if (v == c) {
                ckmax(cur, dp[v][1].sqry(lid) + r*x);
                debug(dp[v][1].sqry(lid) + r*x);
            } else {
                ckmax(cur, dp[v][2].sqry(lid) + r*x + (l-1)*(x+y));
                debug(dp[v][2].sqry(lid) + r*x + (l-1)*(x+y));
            }

#ifdef tmd

            REP (j, i) {
                int jl = rb[j][1], jr = rb[j][0];
                if (rb[j][0] < rb[i][1]) {
                    ckmax(cc, pd[v][j] + (r-l+1)*x);
                } else if (jl < rb[i][1] && rb[i][1] <= jr) {
                    if (v == c) {
                        ckmax(cc, pd[v][j] + (r-rb[j][0])*x);
                    } else {
                        ckmax(cc, pd[v][j]+(r-jr)*x-(jr-l+1)*(x+y));
                    }
                }

            }
/*
dp[c][i] = cover <= r[i] with r[i] covered c
dp[c][i] = dp[*][j] + (r[i]-l[i]+1)*x for r[j] < r[i]
dp[c][i] = dp[c][j] + (r[i]-r[j])*x for r[j] in [l[i],r[i]]
         = dp[c][j] -r[j]*x + r[i]*x
dp[c][i] = dp[!c][j] + (r[i]-r[j])*x - (r[j]-l[i]+1)*(x+y) for r[j] in [l[i],r[i]]
         = dp[!c][j] -r[j]*(2*x+y) + r[i]*x + (l[i]+1)*(x+y)
*/

#endif // tmd
        }

        debug(i, c, l, r, L, R, cur, cc);
        dp[c][0].schg(i,cur);
        dp[c][1].rchg(lid, rid, cur-r*x);
        dp[c][2].rchg(lid, rid, cur-r*(2*x+y));

        ckmax(ans, cur);
#ifdef tmd
        ckmax(cans, cc);
        assert(cc == cur);
        REP (j, 3) {
            pd[j][i] = -INF;
        }
        pd[c][i] = cc;

#endif // tmd
    }

    cout << ans << endl;
    debug(cans);

}
/*
21 6 8 7
2 1 2
3 3 5
3 2 2
1 2 3
1 1 9
3 2 9
*/
