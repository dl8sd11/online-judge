#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
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
#define TIME(i) Timer i(#i)
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
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 11;
const ll MAXN2 = 102;

// dp[step][cur][x][y] = {steps, changes}
int n, a[MAXN][MAXN], dp[MAXN2*2 + 4][MAXN2][MAXN][MAXN][3];
pii pos[MAXN*MAXN];

bool valid (int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

int dx[] = {-1, 1, 2, 2, 1, -1, -2, -2};
int dy[] = {-2, -2, -1, 1, 2, 2, 1, -1};

void upd (int from, int &to) {
    to = min(to, from);
}
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n) {
        REP (j, n) {
            cin >> a[i][j];
            pos[a[i][j]] = {i, j};
        }
    }

    MEM(dp, iNF);

    REP (i, 3) {
        dp[0][1][pos[1].X][pos[1].Y][i] = 0;
    }

    pii ans = {iNF, iNF};
    REP (step, MAXN2*2) {
        REP1 (cur, n*n) {
            REP (x, n) {
                REP (y, n) {
                    // 0 : knight
                    { 
                        auto dp_cur = dp[step][cur][x][y][0];
                        REP (d, 8) {
                            int cx = x + dx[d];
                            int cy = y + dy[d];
                            if (valid(cx, cy)) {
                                int cnxt = (a[cx][cy] == cur + 1) ? cur + 1 : cur;
                                upd(dp_cur, dp[step+1][cnxt][cx][cy][0]);
                            }
                        }

                        upd(dp_cur + 1, dp[step+1][cur][x][y][1]);
                        upd(dp_cur + 1, dp[step+1][cur][x][y][2]);
                    }

                    // 1 : bishop
                    {
                        auto dp_cur = dp[step][cur][x][y][1];
                        REP (r, 2) {
                            REP (d, n) {
                                int cx = d;
                                int cy = r ? x + y - d : d - x + y;
                                if ((cx != x || cy != y) && valid(cx, cy)) {
                                    int cnxt = (a[cx][cy] == cur + 1) ? cur + 1 : cur;
                                    upd(dp_cur, dp[step+1][cnxt][cx][cy][1]);
                                }
                            }
                        }

                        upd(dp_cur + 1, dp[step+1][cur][x][y][0]);
                        upd(dp_cur + 1, dp[step+1][cur][x][y][2]);
                    }

                    // 2 : rook
                    {
                        auto dp_cur = dp[step][cur][x][y][2];
                        REP (r, 2) {
                            REP (d, n) {
                                int cx = r ? d : x;
                                int cy = r ? y : d;
                                if ((cx != x || cy != y) && valid(cx, cy)) {
                                    int cnxt = (a[cx][cy] == cur + 1) ? cur + 1 : cur;
                                    upd(dp_cur, dp[step+1][cnxt][cx][cy][2]);
                                }
                            }
                        }

                        upd(dp_cur + 1, dp[step+1][cur][x][y][1]);
                        upd(dp_cur + 1, dp[step+1][cur][x][y][0]);

                    }

                    if (cur == n * n) {
                        int mn_chg = iNF;
                        REP (i, 3) {
                            mn_chg = min(mn_chg, dp[step][cur][x][y][i]);
                        }
                        if (mn_chg == iNF) {
                            continue;
                        }
                        if (step < ans.X) {
                            ans = {step, mn_chg};
                        } else if (step == ans.X) {
                            ans.Y = min(ans.Y, mn_chg);
                        }
                    }
                }
            }
        }
    }
    debug(dp[183][100][1][6][0]);
    debug(dp[183][100][1][6][1]);
    debug(dp[183][100][1][6][2]);
    debug(dp[184][100][1][6][0]);
    debug(dp[184][100][1][6][1]);
    debug(dp[184][100][1][6][2]);

    cout << ans.X << " " << ans.Y << endl;
    return 0;
}
