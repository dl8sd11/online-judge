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
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 100005;

ll n,p[MAXN];
vector<ll> edge[MAXN];

pii dfs(ll nd,ll par) {
    p[nd] = par;
    pii ret = {nd,0};
    for (auto v : edge[nd]) {
        if (v != par) {
            pii cur = dfs(v,nd);
            if (cur.Y + 1 > ret.Y) {
                ret = cur;
                ret.Y++;
            }
        }
    }
    return ret;
}

ll deg[MAXN];
bool ans = true;
ll chain;
bool chain_top[MAXN];
void cut(ll nd,ll par,ll tp) {
    for (auto v : edge[nd]) {
        if (v != par && SZ(edge[v]) <= 2) {
            cut(v,nd,nd == par ? v : tp);
        }
    }
    if (nd != par && SZ(edge[nd]) == 1) {
        chain_top[tp] = true;
        chain++;
    } 
}
void check(ll nd,ll par,ll dep) {
    if (deg[dep] == 0) {
        deg[dep] = SZ(edge[nd]);
    } else if (deg[dep] != SZ(edge[nd])) {
        ans = false;
    }
    for (auto v : edge[nd]) {
        if (v != par && !chain_top[v]) {
            check(v,nd,dep+1);
        }
    }
}

void check2(ll nd,ll par,ll dep) {
    if (deg[dep] == 0) {
        deg[dep] = SZ(edge[nd]);
    } else if (deg[dep] != SZ(edge[nd])) {
        ans = false;
    }
    for (auto v : edge[nd]) {
        if (v != par) {
            check2(v,nd,dep+1);
        }
    }
}

void valid(ll rt) {
    ans = true;
    MEM(deg,0);
    check2(rt,rt,0);
    if (ans) {
        cout << rt << endl;
        exit(0);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    ll far = dfs(1,1).X;
    pii ep = dfs(far,far);
    debug(far,ep);
    ll cen = ep.X;
    REP (i,ep.Y/2) {
        cen = p[cen];
    }
    debug(cen);

    vector<ll> can = {far,ep.X,cen};
    for (auto c : can) {
        ans = true;
        chain = 0;
        MEM(deg,0);
        MEM(chain_top,0);
        cut(c,c,0);
        pary(chain_top+1,chain_top+n+1);
        debug(c,chain);
        if (chain == 0) {
            valid(c);
        } else if (chain == SZ(edge[c])) {
            vector<ll> len;
            for (auto v : edge[c]) {
                len.eb(dfs(v,c).Y);
            }
            debug(len);
            vector<ll> uni;
            uni = len;
            sort(ALL(uni));
            uni.resize(unique(ALL(uni))-uni.begin());

            if (SZ(uni) == 1) {
                valid(c);
            } else if (SZ(uni) == 2) {
                ll cnt0 = 0, cnt1 = 0;
                ll id0 = -1,id1 = -1;
                REP (i,SZ(len)) {
                    if (len[i] == uni[0]) {
                        cnt0++;
                        id0 = i;
                    } else {
                        cnt1++;
                        id1 = i;
                    }
                }
                if (cnt0 == 1) {
                    valid(dfs(edge[c][id0],c).X);
                } else if (cnt1 == 1) {
                    valid(dfs(edge[c][id1],c).X);
                }
            }
        } else if (chain == 1) {
            ll rt = -1;
            for (auto v : edge[c]) {
                if (chain_top[v]) {
                    rt = dfs(v,c).X ;
                    break;
                } 
            }
            valid(rt);
        }

    }
    cout << -1 << endl;
    return 0;
}
