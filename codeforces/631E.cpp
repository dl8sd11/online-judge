#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
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
const int iNF = 0x3f3f3f3f;
const ll MAXN = 200005;

ll n, a[MAXN], p[MAXN], aii;
pii line[MAXN];
vector<ll> hull;

/*
    Rsum[i][j] = aii - p[j] + p[i] + (j-i)*a[i]
              = j*a[i] - p[j] + (aii + p[i] - i*a[i])

    Lsum[i][j] = aii + p[i-1] - p[j-1] + (j-i) * a[i]
               = j*a[i] -p[j-1] + (aii + p[i-1] - i*a[i])
*/

ld getX(ll l1, ll l2) {
    return (ld(line[l2].Y) - line[l1].Y) / (line[l1].X - line[l2].X);
}

ll getY(ll id, ll x) {
    return x * line[id].X + line[id].Y;
}

void addLine1 (ll id) {
    while (SZ(hull)>=2 && getX(hull[SZ(hull)-1],hull[SZ(hull)-2]) <= getX(id,hull[SZ(hull)-2])) {
        hull.pop_back();
    }
    hull.push_back(id);
}

ll solve1 (ll x) {
    ll L = 0, R = SZ(hull);
    while (L < R - 1) {
        ll mid = (L + R) >> 1;
        if (x <= getX(hull[mid],hull[mid-1])) {
            L = mid;
        } else {
            R = mid;
        }
    }
    debug(L);
    return getY(hull[L], x);
}

void addLine2 (ll id) {
    while (SZ(hull)>=2 && getX(hull[SZ(hull)-1],hull[SZ(hull)-2]) >= getX(id,hull[SZ(hull)-2])) {
        hull.pop_back();
    }
    hull.push_back(id);
}

ll solve2 (ll x) {
    ll L = 0, R = SZ(hull);
    while (L < R - 1) {
        ll mid = (L + R) >> 1;
        if (x <= getX(hull[mid],hull[mid-1])) {
            R = mid;
        } else {
            L = mid;
        }
    }
    debug(L);
    return getY(hull[L], x);
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP1 (i, n) {
        cin >> a[i];
        aii += a[i] * i;
        p[i] = p[i-1] + a[i];
    }

    ll ans = aii;
    for (ll i=n;i >=1; i--) {
        line[i] = pii(i, -p[i]);
        addLine1(i);
        debug(hull);
        ans = max(ans, solve1(a[i]) + (aii + p[i] - i*a[i]));
    }   

    debug(ans);

    hull.clear();
    REP1 (i,n) {
        line[i] = pii(i, -p[i-1]);
        addLine2(i);
        debug(hull);
        ans = max(ans, solve2(a[i]) + (aii + p[i-1] - i*a[i]));
    }   
    pary(line, line+n);


    cout << ans << endl;

    return 0;
}
