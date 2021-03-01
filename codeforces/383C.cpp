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
const ll MAXN = 200005;

ll n,m,a[MAXN],in[MAXN],out[MAXN],dep[MAXN],ts;
vector<ll> edge[MAXN];

namespace SEG {
    ll seg[MAXN*2];
    void add(ll l,ll r,ll val) {
        for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
            if (l&1) {
                seg[l++] += val;
            }
            if (r&1) {
                seg[--r] += val;
            }
        }
    }

    ll query(ll pos) {
        ll ret = 0;
        for (pos+=n;pos>0;pos>>=1) {
            ret += seg[pos];
        }
        return ret;
    }
}

void dfs(ll nd,ll par) {
    in[nd] = ts++;
    dep[nd] = dep[par] + 1;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v,nd);
        }
    }
    out[nd] = ts;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP1 (i,n) {
        cin >> a[i];
    }

    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs(1,1);

    while (m--) {
        ll cmd, x, val;
        cin >> cmd >> x;
        if (cmd == 1) { // add
            cin >> val;
            if (dep[x] & 1 ^ 1) {
                val = -val;
            }
            SEG::add(in[x],out[x],val);
        } else { // query
            cout << a[x] + SEG::query(in[x]) * ((dep[x] & 1) ? 1 : -1) << endl;
        }
    }
    return 0;
}
