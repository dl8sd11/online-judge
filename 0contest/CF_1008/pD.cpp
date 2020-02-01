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
const ll MAXN = 100000;

ll t;
ll a[3];
vector<ll> d[4];
ll solve(ll val,ll idx) {
    d[idx].clear();
    vector<ll> rd;
    for (ll i=1;i*i<=val;i++) {
        if (val % i == 0) {
            d[idx].emplace_back(i);
            if (i*i != val) {
                rd.emplace_back(val/i);
            }
        }
    }
    while (rd.size()) {
        d[idx].emplace_back(rd.back());
        rd.pop_back();
    }
    return SZ(d[idx]);
}
vector<ll> uni(MAXN);
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        ll ans = 1;
        REP (i,3) {
            cin >> a[i];
            ans *= solve(a[i],i);
        }
        ll cd = solve(__gcd(__gcd(a[0],a[1]),a[2]),3);
        ll i01 = solve(__gcd(a[0],a[1]),3); 
        ll i21 = solve(__gcd(a[2],a[1]),3); 
        ll i02 = solve(__gcd(a[0],a[2]),3); 
        ans -= i01*(i01-1)/2*SZ(d[2])   ;
        ans -= i21*(i21-1)/2*SZ(d[0]);
        ans -= i02*(i02-1)/2*SZ(d[1]);
        ans += cd * (cd - 1);
        debug(ans);
        ans -= i01 * i02 * i21;
        ans += cd;
        // REP (idx,3){
        //     reverse(ALL(d[idx]));
        // }
        // pary(d,d+3);
        // while (SZ(d[0]) || SZ(d[1]) || SZ(d[2])) {
        //     ll mn = INF;
        //     REP (i,3) {
        //         if (SZ(d[i])) {
        //             mn = min(mn,d[i].back());
        //         }
        //     }
        //     REP (i,3) {
        //         if (SZ(d[i]) && d[i].back() == mn) {
        //             d[i].pop_back();
        //         }
        //     }
        //     sub++;
        // }
        // debug(sub,cd);
        // ans += cd*3;
        cout <<ans << endl;
    }
    return 0;
}
