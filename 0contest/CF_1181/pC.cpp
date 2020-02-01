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
const ll MAXN = 1003;

ll n,m;
char g[MAXN][MAXN];
vector<pair<char,ll> > col[MAXN];

bool make(ll c,pair<ll,vector<char> > &ret) {
    if (SZ(col[c]) < 3) {
        return false;
    }
    ll s = SZ(col[c]);
    if (col[c][s-1].X != col[c][s-2].X && col[c][s-2] != col[c][s-3]\
    && col[c][s-1].Y == col[c][s-2].Y && col[c][s-2].Y <= col[c][s-3].Y) {
        REP (i,3) {
            ret.Y.eb(col[c][s-i-1].X);
        }
        ret.X = col[c][s-1].Y;
        return true;
    } else {
        return false;
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,n) {
        REP (j,m) {
            cin >> g[i][j];
        }
    }

    REP (j,m) {
        RREP (i,n-1) {
            if (col[j].empty() || col[j].back().X != g[i][j]) {
                col[j].eb(g[i][j],1);
            } else {
                col[j].back().Y++;
            }
        }
    }
    
    ll ans = 0;
    REP (i,n) {
        ll con = 1;
        pair<ll,vector<char>> lst;
        REP (j,m) {
            pair<ll,vector<char>> cur;
            if (make(j,cur)) {
                if (cur == lst) {
                    ans += ++con;
                } else {
                    con = 1;
                    ans++;
                    lst = cur;
                }
            } else {
                con = 1;
                lst = pair<ll,vector<char>>();
            }
            debug(i,j,cur.Y,cur.X);
            if (--col[j].back().Y == 0) {
                col[j].pop_back();
            }
        }
    }

    cout << ans << endl;

    return 0;
}
