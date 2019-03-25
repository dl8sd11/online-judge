#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll MAXN = 100003;
const ll MAXLG = __lg(MAXN) + 3;
ll n,q;
vector<pii> edge[MAXN];
vector<ll> g[MAXN];

bool dead[MAXN],blk[MAXN];
ll dis[MAXN][MAXLG];
map<ll,ll> pd[MAXN];
ll fat[MAXN],lev[MAXN];

priority_queue<pii> pq;

ll OneCentroid(ll root) {
    static vector<ll> sz(n);
    function<void (ll,ll)> get_sz = [&](ll nd,ll par) {
        sz[nd] = 1;
        for (auto v : edge[nd]) {
            if (v.X != par && !dead[v.X]) {
                get_sz(v.X,nd);
                sz[nd] += sz[v.X];
            }
        }
    };
    get_sz(root,-1);

    function<ll (ll,ll)> dfs = [&](ll nd,ll par) {
        for (auto v : edge[nd]) {
            if (v.X != par && !dead[v.X]) {
                if (sz[v.X] > sz[root]/2) {
                    return dfs(v.X,nd);
                }
            }
        }
        return nd;
    };
    return dfs(root,-1);
}

// void calc(ll nd) {
//     pii bst = {-1,-1};
//     for (auto v : g[nd]) {
//         ll x = prev(pd[v].end())->X;
//         debug(v,pd[v]);
//         if (x > bst.X) {
//             bst.Y = bst.X;
//             bst.X = x;
//         } else if (x > bst.Y) {
//             bst.Y = x;
//         }
//     }
//     if (bst.Y != -1) {
//         dp[nd] = bst.X + bst.Y;
//     } else {
//         dp[nd] = -1;
//     }
//     pq.emplace(dp[nd],nd);
// }

void CentroidDecomposition(ll start) {
    function<void (ll,ll,ll)> rec = [&](ll u,ll lv,ll lst) {
        ll c = OneCentroid(u);
        dead[c] = true;
        debug(c);
        lev[c] = lv;

        if (lst != -1) {
            g[lst].emplace_back(c);
        }

        function<void (ll,ll,ll,ll)> build = [&](ll nd,ll par,ll d,ll rt) {
            dis[nd][lev[rt]] = d;
            if (lev[rt] != 0) {
                pd[rt][d+dis[rt][lev[rt]-1]]++;
            }
            for (auto v : edge[nd]) {
                if (v.X != par && !dead[v.X]) {
                    build(v.X,nd,d+v.Y,rt);
                }
            }
        };
        build(c,-1,0,c);

        for (auto v : edge[c]) {
            if (!dead[v.X]) {
                rec(v.X,lv+1,c);
            }
        }
        // calc(c);
    };
    rec(start,0,-1);
}
ll get(ll nd) {
    ll tp = dp[nd].top()
}

ll qry() {

    while (dp[pq.top().Y] != dp[pq.top().Y]) {
        pq.pop();
        assert(pq.size());
    }

    return pq.top().X;
}

void upd(ll start) {
    function<void (ll,ll)> pull = [&](ll nd,ll lst) {
          if (lev[nd] != 0) {
            ll d1 = dis[start][lev[nd]];
            ll d2 = dis[nd][lev[nd]-1];
            pd[nd][d1+d2] += blk[start]?1:-1;
            if (pd[nd][d1+d2] == 0) {
                pd[nd].erase(d1+d2);
            }
        }
        calc(nd);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n-1) {
        ll u,v,w;
        cin >> u >> v >> w;
        edge[u].emplace_back(v,w);
        edge[v].emplace_back(u,w);
    }
    CentroidDecomposition(1);

    cin >> q;
    while (q--) {
        char cmd;
        cin >> cmd;
        if (cmd == 'A') {
            cout << qry() << endl;
        } else {
            ll x;
            cin >> x;
            upd(x);
        }
    }

    return 0;
}
