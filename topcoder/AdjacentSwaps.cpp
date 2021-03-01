#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
const ll MAXN = 52;

/*
 Class: AdjacentSwaps
Method: theCount
Parameters: vector <int>
Returns: int
Method signature: int theCount(vector <int> p)
 */

class AdjacentSwaps {
public:
    int n;
    ll dp[MAXN][MAXN], c[MAXN][MAXN];

    void norm(ll &x) {
        x = x % MOD;
    }

    void solve(vector<int> v, int l, int r) {
        if (dp[l][r] != -1) {
            return;
        } else if (r == l) {
            dp[l][r] = 1;
            return;
        }
        dp[l][r] = 0;
        for (int i=l; i<r; i++) {
            swap(v[i], v[i+1]);
            int mx = -iNF, mn = iNF;
            for (int j=l; j<=r; j++) {
                if (j <= i) {
                    mx = max(mx, v[j]);
                } else {
                    mn = min(mn, v[j]);
                }
            }
            if (mx < mn) {
                solve(v, l, i);
                solve(v, i+1, r);
                debug(l, r, i, dp[l][i], dp[i+1][r], c[r-l-1][i-l]);
                norm(dp[l][r] += dp[l][i] * dp[i+1][r] %MOD * c[r-l-1][i-l]);
                debug(dp[l][r]);
            }
            swap(v[i], v[i+1]);
        }
    }
    
    void build() {
        c[0][0] = 1;
        REP1 (i, n) {
            c[i][0] = 1;
            REP1 (j, i) {
                c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
            }
        }
    }

    int theCount(vector <int> p) {
        n = SZ(p);
        build();
        debug(c[2][0]);
        MEM(dp, -1);
        solve(p, 0, n-1);
        return dp[0][n-1];
    }
};

/********** Good Luck :) **********/
int main()
{
    IOS();
    int n;
    vector<int> p;
    cin >> n;
    REP (i, n) {
        int d;
        cin >> d;
        p.eb(d);
    }

    AdjacentSwaps adjancentswaps;
    cout << adjancentswaps.theCount(p) << endl;
    return 0;
}

/*
20
1 3 0 5 2 7 4 8 10 6 12 9 14 11 16 13 18 15 19 17
 */