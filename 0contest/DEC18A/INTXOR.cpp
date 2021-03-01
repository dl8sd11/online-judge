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
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

ll t,n;
ll a[MAXN];
bool b;

ll pre[MAXN];

ll md(ll idx,ll sz) {
    if (idx > sz) {
        idx -= sz;
    }
    return idx;
}

ll query(ll idx,ll l,ll sz) {
    ll ret = 0;
    cout << 1 << " " << idx+l-1 << " " << md(idx+1,sz)+l-1 << " " << md(idx+2,sz)+l-1 << endl;
    cin >> ret;
    return ret;
}

void solve(ll l,ll r,bool one) {
    debug(l,r,one);
    for (ll i=1;i<=r-l;i++) {
        pre[i] = query(i,l,r-l);
    }
    if (one) {
        ll tmp = 0;
        for (ll i=1;i+3<=r-l;i+=3) {
            tmp ^= pre[i]^pre[i+1];
        }
        a[l+1]  = pre[r-l]^tmp;
        tmp = 0;
        for (ll i=2;i+3<=r-l+1;i+=3) {
            tmp ^= pre[i]^pre[i+1];
        }
        a[l+2] = pre[1]^tmp;
        a[l] = pre[1]^a[l+1]^a[l+2];
        for (ll i=3;i<=r-l;i++) {
            a[l+i-1] = pre[i-2]^a[l+i-3]^a[l+i-2];
        }
    } else {
        ll tmp = 0;
        for (ll i=2;i+3<=r-l;i+=3) {
            tmp ^= pre[i]^pre[i+1];
        }
        a[l]  = pre[r-l]^tmp;
        tmp = 0;
        for (ll i=3;i+3<=r-l+1;i+=3) {
            tmp ^= pre[i]^pre[i+1];
        }
        a[l+1] = pre[1]^tmp;
        
        for (ll i=3;i<=r-l;i++) {
            a[l+i-1] = pre[i-2]^a[l+i-3]^a[l+i-2];
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        cin >> n;
        MEM(a,-1);
        if (n % 3 == 0) {
            solve(1,n-3,0);
            solve(n-3,n+1,1);
        } else {
            solve(1,n+1,n % 3 == 1);
        }

        cout << 2;
        REP1 (i,n) {
            cout << " " << a[i];
        }
        cout << endl;
        cin >> b;
    }
    return 0;
}
