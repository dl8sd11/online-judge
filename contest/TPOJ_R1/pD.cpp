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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=1000000000;
const ll MAXN=3e5+5;
const ll MAXLG=__lg(MAXN)+2;
struct Q{
    ll l,r,ans;
    bool operator < (const Q &cp) {
        if(l==cp.l)return r < cp.r;
        else return l < cp.l;
    }
} query[MAXN];
ll n,q;
set<pii> lxb;
priority_queue<pii,vector<pii>,greater<pii> > pp;
set<ll> st;
ll a[MAXN*2];

void build(){
  for(ll i=n-1;i>0;i--){
    a[i] = min(a[i<<1],a[i<<1|1]);
  }
}

ll qry(ll l,ll r){
  ll ret = INF;
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)ret = min(ret,a[l++]);
    if(r&1)ret = min(ret,a[--r]);
  }
  return ret;
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin>>n>>q;
    REP (i,q) cin>>query[i].l>>query[i].r>>query[i].ans;
    sort(query,query+q);

    ll qi = 0;
    REP1 (i,n) {
        while (qi<q && query[qi].l <= i) {
            lxb.insert({query[qi].ans,qi});
            pp.emplace(query[qi].r,qi);
            st.insert(query[qi].ans);
            qi++;
        }
        
        while(pp.size() && pp.top().X < i){
            debug(pp.top());
            lxb.erase({query[pp.top().Y].ans,pp.top().Y});
            pp.pop();
        }

        if (st.empty()) {
            a[n+i-1] = INF;
            continue;
        }
        auto ptr = st.lower_bound((*prev(lxb.end())).X);
        if(ptr == st.end()){
            a[n+i-1] = INF;
        } else {
            a[n+i-1] = (*ptr);
            st.erase(ptr);
        }
    }

    pary(a+n,a+n*2);
    build();
    bool flag = 0;
    REP(i,q){
        debug(qry(query[i].l-1,query[i].r));
        if(qry(query[i].l-1,query[i].r) != query[i].ans) flag = 1;
    }

    if(flag) cout<<"No"<<endl;
    else {
        cout<<"Yes"<<endl;
        REP(i,n) {
            cout<<a[i+n]<<" \n"[i==n-1];
        }
    }
    return 0;
}
