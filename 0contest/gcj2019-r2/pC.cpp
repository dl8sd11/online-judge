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
const ll INF = 0x3f3f3f3f;
// const ll MAXN = 

ll t,n;
pii m[20];
ll ud(ll a,ll b) {
    if (b == 0) {
        return INF;
    }
    ll ret = (a+b-1)/b;
    if (ret * b == a) {
        ret++;
    }
    return ret;
}
ll dd(ll a,ll b) {
    if (b == 0) {
        return INF;
    }
    ll ret = (a)/b;
    if (ret * b == a) {
        ret--;
    }
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    REP1 (test,t) {
        cin >> n;
        pii mn = {0,1},mx = {INF,1};
        bool imp = false;
        REP (i,n) {
            cin >> m[i].X >> m[i].Y;
            if (i > 0) {
                ll a = m[i-1].X - m[i].X;
                ll b = m[i].Y - m[i-1].Y;
                debug(a,b);
                if (a > 0) { // ax < by
                    if (b > 0 && mn.X*b < mn.Y*a) {
                        mn = {a,b};
                    }
                } else if (a == 0) {
                    if (b < 0) {
                        imp = true;
                    }
                } else { // ax > by
                    a *= -1;
                    b *= -1;
                    if (b < 0) {
                        imp = true;
                    } else {
                        ll gcd = __gcd(a,abs(b));
                        a /= gcd, b /= gcd;
                        if (mx.X == INF || mx.X*b > mx.Y*a) {
                            mx = {a,b};
                        }
                    }
                }

            }
        }

        debug(mn,mx);

        if (imp) {
            cout << "Case #" << test << ": IMPOSSIBLE" << endl;
        } else {
            ll L = 0, R = INF;
            while (L < R - 1) {
                ll mid = (L + R) >> 1;
                ll l = ud(mn.X*mid,mn.Y),r = dd(mx.X*mid,mx.Y);
                
                if (l <= r) {
                    R = mid;
                } else {
                    L = mid;
                }
            }

            ll aR = 0;
            for (ll i=max(1LL,R-10000000);i<min(INF,R+10000000LL);i++) {
                ll l = ud(mn.X*i,mn.Y),r = dd(mx.X*i,mx.Y);
                if (l <= r) {
                    cout << "Case #" << test << ": " << i << " " << ud(mn.X*i,mn.Y) << endl;
                    break;
                }
            }
        }


    }
    return 0;
}
