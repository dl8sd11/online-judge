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
const ll MAXN=2e5+5;
const ll MAXLG=__lg(MAXN)+2;
ll t,n;
string s,tmp,rs;
ll seg[MAXN*2];
ll L[MAXN],R[MAXN],mn[MAXN];
void build() {
    for (ll i=n-1;i>0;i--) {
        seg[i] = min(seg[i<<1],seg[i<<1|1]);
    }
}

ll query(ll l,ll r) {
    if(l == r) return INF;
    ll ret = INF;
    for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
        if (l&1) ret = min(ret,seg[l++]);
        if (r&1) ret = min(ret,seg[--r]);
    }
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    vector<ll> num;
    for (ll i=0;i<=9;i++) num.eb(i);
    for (ll i=1;i<=9999;i++) {
        s = to_string(i);
        rs = s;
        reverse(ALL(rs));
        num.pb(stoi(s + rs));
        for (ll i=0;i<=9;i++) {
            num.pb(stoi(s + char(i+'0') + rs));
        }
    }

    sort(ALL(num));

    n = num.size();
    R[n] = INF;
    for (ll i=0;i<n-1;i++) {
        R[i] = num[i+1] - num[i];
    }
    L[0] = INF;
    for (ll i=1;i<n;i++) {
        L[i] = num[i] - num[i-1];
    }

    for (ll i=0;i<n;i++) {
        seg[i+n] = min(L[i],R[i]);
    }
    build();
    cin>>t;
    while (t--) {
        ll l,r;
        cin>>l>>r;
        ll lidx = lower_bound(ALL(num),l) - num.begin();
        ll ridx = upper_bound(ALL(num),r) - num.begin() - 1;
        if (ridx - lidx + 1 < 2) {
            cout<<-1<<endl;
        } else {
            cout<<min(query(lidx+1,ridx),min(R[lidx],L[ridx]))<<endl;
        }
    }
    return 0;
}
