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
const ll MAXN = 1000003;

ll n,b;
bitset<MAXN> sieve;
vector<ll> prime;

void linear_sieve() {
    for (ll i=2;i<MAXN;i++) {
        if (!sieve[i]) {
            prime.emplace_back(i);
        }
        for (ll j=0;j<SZ(prime) && prime[j]*i<MAXN;j++) {
            sieve[prime[j]*i] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
vector<pii> pvec;
/********** Good Luck :) **********/
int main()
{
    IOS();
    linear_sieve();
    cin >> n >> b;
    ll tb = b;
    for (ll i=0;i<SZ(prime) && prime[i]*prime[i] <= b;i++) {
        ll cnt = 0;
        while (tb % prime[i] == 0) {
            tb /= prime[i];
            cnt++;
        }
        if (cnt) {
            pvec.emplace_back(prime[i],cnt);
        }
    }
    if (tb > 1) {
        pvec.emplace_back(tb,1);
    }
    debug(pvec);


    ll ans = INF;
    for (auto p : pvec) {
        ll sum = 0,cur = p.X;
        while (n / cur > 0) {
            sum += n / cur;
            if (cur > ((n+10)/p.X)) {
                break;
            }
            cur *= p.X;
        }
        ans = min(ans,sum / p.Y);
    }

    cout << ans << endl;
    return 0;
}
