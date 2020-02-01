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
const ll MAXN = 302;

int t, h, s, k, l[MAXN*MAXN], ans[MAXN*MAXN], ptr[MAXN];
bool p[MAXN][MAXN];
int lst[2][MAXN], dp[MAXN*2][MAXN*2][3];

void solve() {
    MEM(lst, -1);
    MEM(ptr, 0);
    vector<int> sz, gp;

    REP (i, h) {
        pary(p[i], p[i]+s);
    } 
    REP (la, MAXN*3) {
        int cs = 0, cg = 0;
        REP (i, s) {
            while (ptr[i] < h && p[ptr[i]][i] == (la&1)) {
                cg += ptr[i] - lst[la&1][i] -1;
                cs++;
                lst[la&1][i] = ptr[i];
                ptr[i]++;
            }
        }
        if (cs == 0) {
            break;
        }
        sz.eb(cs);
        gp.eb(cg);
    }

    if (sz.empty()) {
        return;
    }

    MEM(dp, INF);

    dp[0][0][0] = 0;
    REP (i, MAXN*2) {
        REP (j, MAXN*2) {
            dp[i][j][0] = max({dp[i-1][j][0],dp[i-1][j][1],dp[i-1][j][2]});
            dp[i][j][1] = dp[i-2][j-2][1];// .....

            // contest ended but not done
        }
    }
    debug(sz);
    debug(gp);
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    REP1 (testcase, t) {
        cout << "Case #" << testcase <<  ": ";
        cin >> h >> s >> k;
        REP (i, h) {
            REP (j, s) {
                char c;
                cin >> c;
                p[i][j] = c == 'A';
            }
        }
        REP (i, k) {
            cin >> l[i];
        }

        MEM(ans, INF);

        REP (T, 2) {
            solve();
            REP (i, h) {
                REP (j, s) {
                    p[i][j] ^= 1;
                }
            }
        }

        REP (i, k) {
            cout << ans[i] << " \n"[i==k-1];
        }
    }
    return 0;
}
