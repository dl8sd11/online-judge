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
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=5e5+5;
const ll MAXLG=__lg(MAXN)+2;
ll n,k;
vector<ll> d;
vector<ll> rd;
vector<ll> dx[MAXN];
double p[MAXN];
ll in[MAXN];
ll myexp(ll a,ll b){
  ll t,y;
  t=1; y=a;
  while (b!=0){
    if (b&1==1) t=t*y%MOD;
    y=y*y%MOD; b=b>>1;
  }
  return t;
}


ll inv(ll a){
  return myexp(a,MOD-2);
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;
    for (ll i=1;i*i<=n;i++) {
        if (n % i == 0) {
            d.push_back(i);
            rd.push_back(n/i);
        } 
    }
    if (d.back() == rd.back()) {
        d.pop_back();
    }
    reverse(ALL(rd));
    for (auto dd:rd) {
        d.push_back(dd);
    }


    REP (i,SZ(d)) {
        REP (j,SZ(d)) {
            if (d[j] % d[i] == 0) {
                dx[j].pb(i);
            }
        }
    }

    REP (i,SZ(d)) {
        in[i] = inv(SZ(dx[i]));
    }

    p[SZ(d)-1] = 1;
    REP (s,k) {
        REP (i,SZ(d)) {
            double tp = p[i];
            p[i] = 0;
    
            REP (j,SZ(dx[i])) {

                // p[dx[i][j]] = (p[dx[i][j]] + tp * in[i] % MOD) % MOD;
                p[dx[i][j]] += tp / SZ(dx[i]);
            }
        }
    }

    pary(p,p+SZ(d));
    ll ans = 0;
    REP (i,SZ(d)) {
        // ans = (ans + d[i] * p[i] % MOD) % MOD;
    }

    cout << ans << endl;
    return 0;
}
