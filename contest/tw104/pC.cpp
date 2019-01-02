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
const ll MAXN=5003;
const ll MAXLG=__lg(MAXN)+2;

ll mx[MAXN][MAXLG];
ll t,n;
ll a[MAXN];
ll idx[MAXN];
ll mn[MAXN][MAXLG];

void build() {
    REP (i,n) {
        mx[i][0] = idx[i];
        mn[i][0] = idx[i];
    }
    for (ll i=1;i<MAXLG;i++) {
        for (ll l=0;l+(1<<i)<=n;l++) {
            mx[l][i] = max(mx[l][i-1],mx[l+(1<<i-1)][i-1]);
            mn[l][i] = min(mn[l][i-1],mn[l+(1<<i-1)][i-1]);
        }
    }
}

ll query(ll l,ll r,bool big) {
    ll e = __lg(r-l+1);
    if (big) {
        return max(mx[l][e],mx[r-(1<<e)+1][e]);
    } else {
        return min(mn[l][e],mn[r-(1<<e)+1][e]);
    }
}


/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        cin >> n;
        REP (i,n) {
            cin >> a[i];
            idx[--a[i]] = i;
        }

        build();
        
        ll ans = 0;
        REP (r,n) {
            REP (l,r) {
                ll L = min(a[l],a[r]);
                ll R = max(a[l],a[r]);

                if (r==query(L,R,1) && l==query(L,R,0) && R-L == r-l) {
                    ans++;
                    debug(l,r);
                }
            }
        } 

        cout << ans << endl;
    }
    return 0;
}
