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
const ll MAXN = 100003;



ll n,q;
ll OneCentroid(ll root, const vector<vector<ll>> &edge, const vector<bool> &dead) {
    static vector<ll> sz(n);
    function<void (ll, ll)> get_sz = [&](ll nd,ll par) {
        sz[nd] = 1;
        for (auto v : edge[nd]) {
            if (v != par && !dead[v]) {
                get_sz(v,nd);
                sz[nd] += sz[v];
            }
        }
    };
    get_sz(root,root);
    ll rsz = sz[root];
    function<ll (ll, ll)> dfs = [&](ll nd,ll par) {
        for (auto v : edge[nd]) {
            if (v != par && !dead[v]) {
                if (sz[v] > rsz/2) {
                    return dfs(v,nd);
                }
            }
        }
        return nd;
    };
    return dfs(root,root);
}
vector<ll> CentroidDecomposition(const vector<vector<ll>> &edge,const vector<vector<pii>> &query) {
    vector<ll> ans(q);
    vector<bool> dead(n,false);
    function <void (ll)> rec = [&](ll start) {
        ll c = OneCentroid(start,edge,dead);
        dead[c] = true;
        for (auto v : edge[c]) {
            if (!dead[v]) {
                rec(v);
            }
        }

        map<ll,ll> dist;
        function<void (ll,ll,ll,bool)> add_dist = [&](ll nd,ll par,ll d,bool add) {
            dist[d] += (add ? 1 : -1);
            for (auto v : edge[nd]) {
                if (v != par && !dead[v]) {
                    add_dist(v,nd,d+1,add);
                }
            }
        };

        function<void (ll,ll,ll)> push = [&](ll nd,ll par,ll d) {
            for (auto it : query[nd]) {
                ll dd, qid;
                tie(dd,qid) =  it;
                if (dd - d >= 0 && dist.count(dd-d)) {
                    ans[qid] += dist[dd-d];
                }
            }
            for (auto v : edge[nd]) {
                if (v != par && !dead[v]) {
                    push(v,nd,d+1);
                }
            }
        };


        add_dist(c,c,0,true);
        for (auto it : query[c]) {
            ll dd, qid;
            tie(dd,qid) = it;
            ans[qid] += dist[dd];
        }

        for (auto v : edge[c]) {
            if (!dead[v]) {
                add_dist(v,c,1,false);
                push(v,c,1);
                add_dist(v,c,1,true);
            }
        }
        dead[c] = false;
    };

    rec(0); 
    return ans;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> q;

    vector<vector<ll>> edge(n);
    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        u--,v--;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }
    

    vector<vector<pii>> query(n);
    REP (i,q) {
        ll u,v;
        cin >> u >> v;
        u--;
        query[u].emplace_back(v,i);
    }

    auto ans = CentroidDecomposition(edge,query);

    for (auto el : ans) {
        cout << el << endl;
    }

    return 0;
}
