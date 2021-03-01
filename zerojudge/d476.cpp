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
const ll MAXN = 400001;


ll n,m;
ll a[MAXN],bit[MAXN];

ll qry(ll pos) {
    ll ret = 0;
    pos++;
    for (;pos>=1;pos-=-pos&pos) {
        ret += bit[pos];
    }
    return ret;
}

ll qry(ll L,ll R) {
    return qry(R) - qry(L-1);
}

void add(ll pos,ll val) {
    pos++;
    for (;pos<MAXN;pos+=-pos&pos) {
        bit[pos] += val;
    }
}

struct Query {
    bool type; // mody : 1
    pii data; // mody: pos,delta query: l,r
    ll k,ans;
};
#ifdef tmd
ostream& operator << (ostream &_s,const Query &_p){
    return _s<<"("<<_p.type<<","<<_p.data<<","<<_p.k<<","<<_p.ans<<")";
}
#endif
vector<Query> query;
vector<ll> rng;

void solve(vector<ll> V,ll L,ll R) {
    if (R == L + 1) {
        for (auto v : V) {
            query[v].ans = rng[L];
        }
    } else {
        ll mid = (L + R) >> 1;
        debug(L,mid,R);
        vector<ll> lV,rV;
        for (auto v : V) {
            debug(query[v]);
            if (query[v].type == 0) {
                ll cnt = qry(query[v].data.X,query[v].data.Y);
                debug(cnt);
                if (cnt > query[v].k) {
                    lV.eb(v);
                } else {
                    rV.eb(v);
                    query[v].k -= cnt;
                }
            } else {
                if (query[v].data.X < mid) {
                    lV.eb(v);
                    add(query[v].k,query[v].data.Y);
                } else {
                    rV.eb(v);
                }
            }
        }

        debug(V,lV,rV);
        solve(rV,mid,R);

        for (auto v : V) {
            if (query[v].type == 1) {
                if (query[v].data.X < mid) {
                    add(query[v].k,-query[v].data.Y);
                }
            }
        }

        solve(lV,L,mid);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,n) {
        cin >> a[i];
        query.push_back({1,pii(a[i],1),i,-1});
        rng.eb(a[i]);
    }

    while (m--) {
        char cmd;
        cin >> cmd;
        if (cmd == 'Q') {
            ll l,r,k;
            cin >> l >> r >> k;
            k--;
            l--,r--;
            query.push_back({0,pii(l,r),k,-1});
        } else {
            ll idx,v;
            cin >> idx >> v;
            idx--;
            query.push_back({1,pii(a[idx],-1),idx,-1});
            a[idx] = v;
            rng.eb(v);
            query.push_back({1,pii(a[idx],1),idx,-1});
        }
    }

    sort(ALL(rng));
    rng.resize(unique(ALL(rng))-rng.begin());
    debug(rng);

    for (auto &Q : query) {
        if (Q.type) {
            Q.data.X = lower_bound(ALL(rng),Q.data.X)-rng.begin();
        }
    }

    vector<ll> id;
    REP (i,SZ(query)) {
        id.emplace_back(i);
    }
    solve(id,0,SZ(rng));

    for (auto Q : query) {
        if (Q.type^1) {
            cout << Q.ans << endl;
        }
    }
    return 0;
}
