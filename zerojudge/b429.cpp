#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
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
const ll k = sqrt(MOD) + 103;

ll a, b, n;
pii ap[100005];

ll mpow(ll base, ll ep) {
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % n;
        }
        base = base * base % n;
        ep >>= 1;
    }
    return ret;
}

void extGCD(ll A,ll B,ll &x,ll &y) { // A p coprime

    if (B == 0) {
        x = 1;
        y = 0;
        assert(A == 1);
        return;
    }
    ll xx,yy;
    extGCD(B,A%B,xx,yy);
    x = yy;
    y = xx - A/B*yy;
    return;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    while (cin >> a >> b >> n) {
        ll ta = 1;
        ll sz = 0;
        REP (i,k+1) {
            ap[sz++] = pii(ta,i);
            ta = ta * a % n;
        }
        sort(ap,ap+sz);

        ll ans = INF;
        ll sa = mpow(a,k);
        ta = 1;
        REP (i,k+1) {
            ll inv,y;
            extGCD(ta,n,inv,y);

            inv = (inv % n + n) % n * b % n;

            auto ptr = lower_bound(ap,ap+sz,pii(inv,0));
            if (ptr != ap+sz && (*ptr).X == inv) {
                ans = min(ans,i*k+(*ptr).Y);
                break;
            }
            ta = ta * sa % n;
        }

        if (ans == INF) {
            cout << "NOT FOUND" << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}