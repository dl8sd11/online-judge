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

ll n,k;

bool gt(ll num) {
    ll sum = (num + num + k - 1) * k / 2;
    return sum > n;

}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;
    if (k == 1) {
        cout << "YES" << endl;
        cout << n << endl;
        return 0;
    }
    if (n < (k + 1) * k / 2) {
        cout << "NO" << endl;
        return 0;
    }

    if (k == 2) {
        if (n == 4) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            cout << (n-1)/2 << " " << n - (n-1)/2 << endl;
        }
        return 0;
    }

    if (n == 8 && k == 3) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    ll l = -1, r = n;
    while (l < r - 1) {
        ll mid = (l + r) >> 1;
        if (gt(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    debug(r);

    ll sum = 0;
    vector<ll> ans;
    REP (i, k - 2) {
        ans.eb(l + i);
        sum += l + i;
    }

    if (sum + (l + k - 2)*3 < n) {
        ans.eb(l + k - 1);
        ans.eb(n - (sum + l + k - 1));
    } else {
        ans.eb(l + k - 2);
        ans.eb(n - sum - (l + k - 2));
    }

    for (auto v : ans) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
