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

const ll iNF = 10000000010;
const ll MAXN = 1024;

ll t, n, z, a[MAXN], dp[MAXN][MAXN];
deque<ll> hull;
pair<ll,ll> line[MAXN];

pii getX(ll l1, ll l2) {
    return pii((line[l2].Y - line[l1].Y), (line[l1].X - line[l2].X));
}

bool geq(pii A, pii B) {
    if (A.Y < 0) {
        A.X *= -1, A.Y *= -1;
    }
    if (B.Y < 0) {
        B.Y *= -1, B.X *= -1;
    }
    return A.X * B.Y >= B.X * A.Y;
}

ll getY(ll l, ll x) {
    return line[l].X * x + line[l].Y;
}

void addLine(ll id) {
    while (SZ(hull)>=2 && geq(getX(id, hull[SZ(hull)-2]),getX(hull[SZ(hull)-1],hull[SZ(hull)-2]))) {
        hull.pop_back();
    }
    hull.emplace_back(id);
}

ll solve(ll v) {
    while (SZ(hull)>=2 && getY(hull[SZ(hull)-1],v)>=getY(hull[SZ(hull)-2],v)) {
        hull.pop_back();
    }
    return getY(hull.back(), v);
}
/*
    dp[i][j] = min(i*a[k] + dp[k][j-1] - a[k]*(k+1) + a[i])
 */
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        cin >> n >> z;
        REP1 (i, n) {
            cin >> a[i];
        }
        sort(a+1, a+n+1);

        REP (i, n+1) {
            REP (j, z+1) {
                dp[i][j] = iNF;
            }
        }
        dp[0][0] = 0;

        REP1 (j, z) {
            hull.clear();
            line[0] = pii(0, dp[0][j-1]);
            hull.emplace_back(0);
            for (ll i=max(1,j-1);i<=n;i++) {
            // REP1 (i, n) {
                if (j == z) {
                    debug(hull);
                }
                dp[i][j] = solve(i) + a[i];
                line[i] = pii(a[i], dp[i][j-1]-a[i]*(i+1));
                addLine(i);
            }
            pary(line, line+n);
        }

        debug(dp[2][2]);
        ll ans = iNF;
        REP1 (i, n) {
            ans = min(ans, dp[i][z] + a[i]*(n-i));
        }
        cout << ans << endl;
    }
    return 0;
}