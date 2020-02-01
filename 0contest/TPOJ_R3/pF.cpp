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
const ll MAXN = 60003;

ll n,a[MAXN];

bool solve1(ll k) {
    ll sum = 0;
    REP (i,n) {
        sum ^= a[i];
        if (sum <= k) {
            sum = 0;
        }
    }
    if (sum != 0) {
        return false;
    } else{
        return true;
    }
}

ll mx = 0;
bool solve2(ll k) {
    ll sum = 0;
    REP (i,n) {
        sum ^= a[i];
        if (sum <= k) {
            ll cnt = 0;
            while ((i+1) < n && (sum ^ a[i+1]) <= k) {
                cnt++;
                i++;
            }
            mx = max(cnt,mx);
            sum = 0;
        }
    }
    if (sum != 0) {
        return false;
    } else{
        return true;
    }
}

bool solveX(ll k,ll X) {
    ll sum = 0;
    REP (i,n) {
        sum ^= a[i];
        if (sum <= k) {
            ll cnt = 0;
            while (cnt++ < X && (i+1) < n && (sum ^ a[i+1]) <= k) {
                i++;
            }
            sum = 0;
        }
    }
    if (sum != 0) {
        return false;
    } else{
        return true;
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> a[i];
    }
    ll L = -1, R = (1LL)<<33;
    while (L < R - 1) {
        ll mid = (L + R) >> 1;
        if (mid == -1) {
            L = mid;
            continue;
        }
        mx = 0;
        bool ret = solve1(mid) || solve2(mid);
        REP1 (i,1000) {
            ret |= solveX(mid,i);
        }
        REP (i,1000) {
            ret |= solveX(mid,mx-i);
        }
        if (ret) {
            R = mid;
        } else {
            L = mid;
        }
    }

    cout << R << endl;
    return 0;
}
