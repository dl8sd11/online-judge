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

ll t,a,n,b,m;

ll extGCD(ll n1,ll n2,ll &x1,ll &x2) {
    if (n1 == 0) {
        x2 = 1;
        x1 = 0;
        return n2;
    }
    ll cx1,cx2;
    ll ret = extGCD(n2%n1,n1,cx1,cx2);
    x2 = cx1;
    x1 = cx2 - n2/n1*cx1;
    return ret;
}

ll mod;
ll mul(ll v1,ll v2,ll md=mod) {
    return v1 * v2 % md;
}

void normal(ll &v1) {
    v1 %= mod;
    if (v1 < 0) {
        v1 += mod;
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();

    cin >> t;
    while (t--) {
        cin >> a >> n >> b >> m;
        ll r1,r2;
        ll gcd = extGCD(n,m,r1,r2);
        if ((b-a) % gcd != 0) {
            cout << "no solution" << endl;
            continue;
        }
        mod = n * m / gcd;

        ll ans = mul(mul(r1,(b-a)/gcd,m/gcd),n) + a;
        normal(ans);

        cout << ans << " " << mod <<  endl;

    }
    return 0;
}
