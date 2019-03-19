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
// const ll MAXN = 

struct Info {
    ll dis,sz,mi;
};
ll OneCentroid(ll root,const vector<vector<pii>> &edge,vector<bool> &dead) {
    static vector<ll> sz(edge.size());
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
    ll hf = sz[root] / 2;
    function<ll (ll,ll)> dfs = [&](ll nd,ll par) {
        for (auto v : edge[nd]) {
            if (v.X != par && !dead[v.X] && sz[v.X] > hf) {
                return dfs(v.X,nd);
            }
        }
        return nd;
    };
    return dfs(root,root);
}

void CentroidDecomposition(const vector<vector<pii>> &edge,vector<ll> &pG,vector<vector<ll>> &anc,vector<ll> &dep) {
    ll n = SZ(edge);
    vector<bool> dead(n);

    function<void (ll,ll,ll,ll)> get_child = [&](ll nd,ll par,ll d,ll lev) {
        anc[nd][lev] = d;
        for (auto v : edge[nd]) {
            if (v.X != par && !dead[v.X]) {
                get_child(v.X,nd,d+v.Y,lev);
            }
        }
    };
    function<void (ll,ll,ll)> rec = [&](ll start,ll par,ll lev) {
        ll c = OneCentroid(start,edge,dead);
        dead[c] = true;
        pG[c] = par;
        dep[c] = lev;

        get_child(c,-1,0,lev);

        for (auto v : edge[c]) {
            if (!dead[v.X]) {
                rec(v.X,c,lev+1);
            }
        }

        dead[c] = false;
    };
    rec(0,-1,0);
}

void upd(ll start,vector<Info> &info,const vector<ll> &pG,const vector<vector<ll>> &anc,const vector<ll> &dep) {
    function<void (ll)> pull = [&](ll nd) {
        info[nd].dis += anc[start][dep[nd]]; //lower_bound(ALL(child[nd]),pii(start,-1))->Y;
        info[nd].sz++;
        if (pG[nd] != -1) {
            info[nd].mi += anc[start][dep[nd]-1];//lower_bound(ALL(child[pG[nd]]),pii(start,-1))->Y;
            pull(pG[nd]);
        }
    };
    pull(start);
}

ll qry(ll start,const vector<Info> &info,const vector<ll> &pG,const vector<vector<ll>> &anc,const vector<ll> &dep) {
    ll ret = 0;
    function<void (ll,ll)> pull = [&](ll nd,ll lst) {
        ret += (info[nd].sz-(lst==-1?0:info[lst].sz))*anc[start][dep[nd]] + info[nd].dis;
        if (lst != -1) {
            ret -= info[lst].mi;
        }
        debug(ret);
        if (pG[nd] != -1) {
            pull(pG[nd],nd);
        }
    };
    pull(start,-1);
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    ll n,q;
    cin >> n >> q;

    vector<vector<pii>> edge(n);
    REP (i,n-1) {
        ll a,b,l;
        cin >> a >> b >> l;
        edge[a].emplace_back(b,l);
        edge[b].emplace_back(a,l);
    }

    vector<ll> pG(n);
    vector<vector<ll>> anc(n,vector<ll>(__lg(n)+2));

    vector<ll> dep(n);
    CentroidDecomposition(edge,pG,anc,dep);

    debug(pG);

    vector<Info> info(n); // dist sum, size
    vector<bool> occ(n);

    REP (i,q) {
        ll t,x;
        cin >> t >> x;
        if (t == 1) {
            if (!occ[x]) {
                upd(x,info,pG,anc,dep);
                occ[x] = true;
            }
        } else {
            cout << qry(x,info,pG,anc,dep) << endl;
        }
    }

    return 0;
}


/*
6 100
0 1 1
1 2 2
2 3 3
3 4 4
4 5 5
2 0
2 1
2 2
2 3
2 4
2 5
1 0
2 0
2 1
2 2
2 3
2 4
2 5
1 1
2 0
2 1
2 2
2 3
2 4
2 5
1 2
2 0
2 1
2 2
2 3
2 4
2 5
1 3
2 0
2 1
2 2
2 3
2 4
2 5
1 4
2 0
2 1
2 2
2 3
2 4
2 5
1 5
2 0
2 1
2 2
2 3
2 4
2 5
*/