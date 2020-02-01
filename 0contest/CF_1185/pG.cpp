#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
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
const ll MAXN = 51;

int n,t;
int len[MAXN],gen[MAXN];
int dp01[MAXN][MAXN][MAXN*MAXN];
int dp2[MAXN][MAXN*MAXN];
int pem[3][MAXN][MAXN][MAXN];

inline void add(int &x,int y) {
    x = (x + y) % MOD;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> t;
    REP (i,n) {
        cin >> len[i] >> gen[i];
        gen[i]--;
    }

    dp01[0][0][0] = 1;
    dp2[0][0] = 1;

    REP (i,n) {
        for (int j=t;j>=len[i];j--) {
            if (gen[i] == 2) {
                for (int k=(i+1);k>=1;k--) {
                    add(dp2[k][j],dp2[k-1][j-len[i]]);
                }
            } else if (gen[i] == 1) {
                for (int x=(i+1);x>=0;x--) {
                    for (int y=(i+1-x);y>=1;y--) {
                        add(dp01[x][y][j],dp01[x][y-1][j-len[i]]);
                    }
                }
            } else if (gen[i] == 0) {
                for (int x=(i+1);x>=1;x--) {
                    for (int y=(i+1-x);y>=0;y--) {
                        add(dp01[x][y][j],dp01[x-1][y][j-len[i]]);
                    }
                }
            }
        }
    }


    REP (x,n+1) {
        REP (y,n-x+1) {
            REP (z,n-x-y+1) {
                if (x + y + z == 1) {
                    if (x) {
                        pem[0][1][0][0] = 1;
                    }
                    if (y) {
                        pem[1][0][1][0] = 1;
                    }
                    if (z) {
                        pem[2][0][0][1] = 1;
                    }
                } else {
                    if (x) {
                        pem[0][x][y][z] = ll(pem[1][x-1][y][z] + pem[2][x-1][y][z]) * x % MOD;
                    }
                    if (y) {
                        pem[1][x][y][z] = ll(pem[0][x][y-1][z] + pem[2][x][y-1][z]) * y % MOD;
                    }
                    if (z) {
                        pem[2][x][y][z] = ll(pem[0][x][y][z-1] + pem[1][x][y][z-1]) * z % MOD;
                    }

                }
            }
        }
    }

    // REP (i,n) {
    //     REP (j,n) {
    //         debug(i,j);
    //         pary(dp01[i][j],dp01[i][j]+t+1);
    //     }
    // }

    int ans = 0;
    for (int xy=0;xy<=t;xy++) {
        REP (i,n+1) {
            REP (j,n+1-i) {
                REP (k,n+1-i-j) {
                    int psum = (ll(pem[0][i][j][k]) + pem[1][i][j][k] + pem[2][i][j][k]) % MOD;
                    add(ans,ll(psum)*dp01[i][j][xy]%MOD*dp2[k][t-xy]%MOD);
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}
