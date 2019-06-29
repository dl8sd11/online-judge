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
const ll MAXN = 100005;

ll n, a[MAXN],ans;

ll solve3(ll pos) {
    ll l = a[pos - 1], r = a[pos + 1], c = a[pos];
    if (l > c && r > c) {
        return (n - c + 1) * c;
    } else if (l < c && r > c) {
        return (n - c + 1) * (c - l);
    } else if (l > c && r < c) {
        return (n - c + 1) * (c - r);
    } else if (l < c && r < c) {
        return (n - c + 1) * (c - max(l,r)) - min(l,r) * (n - c + 1);
    }
    assert(false);
    return 0;
}

ll solve2(ll cur,ll nei) {
    if (cur > nei) {
        return (n - cur + 1) * (cur - nei);
    } else {
        return (n - cur + 1) * cur;
    }
}
vector<ll> uni;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> a[i];
        if (i == 0 || a[i] != a[i-1]) {
            uni.eb(a[i]);
        }
    }
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    ll m = SZ(uni);
    REP (i,m) {
        a[i] = uni[i];
    }
    pary(a,a+m);

    ans += solve2(a[0],a[1]);
    ans += solve2(a[m-1],a[m-2]);
    debug(solve2(a[0],a[1]));
    debug(solve2(a[m-1],a[m-2]));
    for (ll i=1;i<m-1;i++) {
        ans += solve3(i);
        debug(solve3(i));
    }

    cout << ans << endl;
    return 0;
}
