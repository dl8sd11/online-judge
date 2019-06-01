#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
/*
    a maxflow algorithm - Dinic
    time complexity - O(V^2E)
    code author - ToMmyDong
    test on - codeforces 1082G
*/

const ll MAXN = 2003;
const ll INF = 0x3f3f3f3f3f3f3f3f;

namespace MAXFLOW {
    ll n,lev[MAXN],ecnt,head[MAXN],cur[MAXN];

    struct Graph {
        ll t,cap,flow,nxt;
    }G[MAXN*4];


    void add_edge(ll f,ll t,ll cap) {
        debug(f,t,cap);
        G[ecnt] = {t,cap,0,head[f]};
        head[f] = ecnt++;
        G[ecnt] = {f,0,0,head[t]};
        head[t] = ecnt++;
    }

    ll dfs(ll nd,ll t,ll lim) {
        if (nd == t || lim == 0) {
            return lim;
        }
        for (ll &i=cur[nd];i!=-1;i=G[i].nxt) {
            ll x = G[i].t;
            if (G[i].cap > G[i].flow && lev[x] == lev[nd] + 1) {
                ll df = dfs(x,t,min(lim,G[i].cap-G[i].flow));
                if (df) {
                    G[i].flow += df;
                    G[i^1].flow -= df;
                    return df;
                }
            }
        }
        return 0;
    }

    bool bfs(ll s,ll t) {
        queue<ll> q;
        q.emplace(s);
        memset(lev,-1,sizeof(lev));
        lev[s] = 0;

        while (q.size()) {
            ll nd = q.front();q.pop();
            if (nd == t) {
                break;
            }
            for (ll i=head[nd];i!=-1;i=G[i].nxt) {
                if (G[i].cap > G[i].flow && lev[G[i].t] == -1) {
                    lev[G[i].t] = lev[nd] + 1;
                    q.emplace(G[i].t);
                }
            }
        }
        return lev[t] != -1;
    }

    ll dinic(ll s,ll t) {
        ll flow = 0;
        while (bfs(s,t)) {
            ll df = 0;
            for (int i=0;i<n;i++) {
                cur[i] = head[i];
            }
            while (df=dfs(s,t,INF)) {
                flow += df;
            }
        }
        return flow;
    }

    void init(int N) {
        n = N;
        memset(head,-1,sizeof(head));
    }
};
vector<ll> prime;
bool sieve[100003];
void linear_sieve() {
    ll mx = sqrt(MOD) + 3;
    for (ll i=2;i<=mx;i++) {
        if (!sieve[i]) {
            prime.eb(i);
        }
        for (ll j=0;j<SZ(prime) && prime[j]*i <100003;j++) {
            sieve[prime[j]*i] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

ll cnt = 1;
struct E {
    ll a;
    vector<pii> fac;
    vector<ll> id;
    void factorize() {
        ll ta = a;
        for (auto p : prime) {
            ll ps = 0;
            while (ta % p == 0) {
                ps ++;
                ta /= p;
            }
            if (ps > 0) {
                fac.eb(p,ps);
                id.eb(cnt++);
            }
        }
        if (ta != 1) {
            fac.eb(ta,1);
            id.eb(cnt++);
        }
    }
}a[103];

/********** Good Luck :) **********/
int main()
{
    IOS();
    ll n,m;
    linear_sieve();
    cin >> n >> m;
    REP1 (i,n) {
        cin >> a[i].a;
        a[i].factorize();
        debug(a[i].fac);
    }

    MAXFLOW::init(cnt+1);
    REP (i,m) {
        ll x,y;
        cin >> x >> y;
        if (x & 1 ^ 1) {
            swap(x,y);
        }
        ll ptr = 0;
        REP (l,SZ(a[x].fac)) {
            auto p = a[x].fac[l];
            while (ptr < SZ(a[y].fac) && a[y].fac[ptr].X < p.X) {
                ptr++;
            }
            if (ptr < SZ(a[y].fac) && a[y].fac[ptr].X == p.X) {
                MAXFLOW::add_edge(a[x].id[l],a[y].id[ptr],INF);
            }
        }
    }

    REP1 (i,n) {
        if (i & 1) {
            REP (j,SZ(a[i].fac)) {
                MAXFLOW::add_edge(0,a[i].id[j],a[i].fac[j].Y);
            }
        } else {
            REP (j,SZ(a[i].fac)) {
                MAXFLOW::add_edge(a[i].id[j],cnt,a[i].fac[j].Y);
            }
        }
    }

    cout << MAXFLOW::dinic(0,cnt) << endl;
    return 0;
}
