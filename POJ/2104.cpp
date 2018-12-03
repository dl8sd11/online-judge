#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<sstream>
#include<cmath>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define MEM(i,n) memset(i,n,sizeof i)
#define X first
#define Y second
#define SZ(_a) (int)_a.size()
#define ALL(_a) _a.begin(),_a.end()
#define pb push_back
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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif


const ll MAXN=1e5+5,MAXlg=__lg(MAXN)+2;
const ll MOD=1000000007;
const ll INF=ll(1e18+7);

ll n,m;
ll a[MAXN],ans[MAXN];
vector<pair<ll,ll> > spos;
ll bit[MAXN];
struct QUERY {
    ll l,r,k;
    QUERY(){}
    QUERY(ll l,ll r,ll k):l(l),r(r),k(k){}
}q[MAXN];

void add(ll pos,ll val) {
    for (pos++;pos<MAXN;pos+=-pos&pos) {
        bit[pos] += val;
    }
}

ll query(ll pos) {
    ll ret = 0;
    for (pos++;pos >= 1;pos-=-pos&pos) {
        ret += bit[pos];
    }
    return ret;
}

ll cnt(ll idx) {
    return query(q[idx].r) - query(q[idx].l-1);
}

ll cur_pos = -1;
void update(ll goal) {
    while (spos[cur_pos+1].X <= goal && cur_pos<n) {
        add(spos[++cur_pos].Y,1);
    }

    while (spos[cur_pos].X > goal && cur_pos >=0) {
        add(spos[cur_pos--].Y,-1);
    }
}
void solve(vector<ll> V,ll L,ll R) {
    debug(V,L,R);
    if (L == R - 1) {
        REP (i,SZ(V)) {
            ans[V[i]] = L;
        }
        return;
    }
    ll mid = L+R>>1;
    update(mid-1);
    debug(mid-1);
    vector<ll> lV,rV;
    REP (i,SZ(V)) {
        debug(cnt(V[i]),V[i]);
        if (cnt(V[i]) < q[V[i]].k) {
            rV.push_back(V[i]);
        } else {
            lV.push_back(V[i]);
        }
    }
    debug(lV,rV);
    solve(lV,L,mid);
    solve(rV,mid,R);
}
int main()
{
    ll min_num = INF;
    ll max_num = -INF;
    scanf("%lld%lld",&n,&m);
    REP (i,n) {
        scanf("%lld",a+i);
        max_num = max(max_num,a[i]);
        min_num = min(min_num,a[i]);
        spos.push_back(make_pair(a[i],i));
    }
    sort(ALL(spos));

    REP (i,m) {
        ll l,r,k;
        scanf("%lld%lld%lld",&l,&r,&k);
        debug(l,r,k);
        l--,r--;
        q[i] = QUERY(l,r,k);
    }

    vector<ll> V;
    REP (i,m) {
        V.push_back(i);
    }
    debug(V);
    solve(V,min_num,max_num+1);

    REP (i,m) {
        printf("%d\n",ans[i]);
    }
}
