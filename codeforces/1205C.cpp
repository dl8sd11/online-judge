#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
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
// const ll MAXN = 

int n;
bool g[2][52][52];
bool dp[2][52][52][52][52];
bool v1[52][52], v2[52][52];
bool vis[2][52][52][52][52];

bool qry (int xa, int ya, int xb, int yb) {
    cout << "? " << xa << " " << ya << " " << xb << " " << yb << endl;
    bool ret;
    cin >> ret;
    return ret;
}

bool valid (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}
bool solve (int id, int xa, int ya, int xb, int yb) {
    if (!valid(xa, ya) || !valid(xb, yb) || xa > xb || ya > yb) {
        return 0;
    } else if (vis[id][xa][ya][xb][yb]) {
        return dp[id][xa][ya][xb][yb];
    } else {
        if (g[id][xa][ya] != g[id][xb][yb]) {
            vis[id][xa][ya][xb][yb] = true;
            return dp[id][xa][ya][xb][yb] = false;
        } else {
            bool ret = xa + ya + 2 > xb + yb;
            ret |= solve(id, xa+1, ya, xb, yb-1);
            ret |= solve(id, xa+1, ya, xb-1, yb);
            ret |= solve(id, xa, ya+1, xb, yb-1);
            ret |= solve(id, xa, ya+1, xb-1, yb);

            vis[id][xa][ya][xb][yb] = true;
            return dp[id][xa][ya][xb][yb] = ret;
        }
    }
}

void ans (int id) {
    cout << "!" << endl;
    REP1 (i, n) {
        REP1 (j, n) {
            cout << g[id][i][j];
        }
        cout << endl;
    }
}
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    cin >> n;
    g[1][1][2] = g[0][1][1] = g[1][1][1] = 1;
    g[0][1][2] = g[0][n][n] = g[1][n][n] = 0;
    v2[1][2] = v1[1][1] = v2[1][1] = 1;
    v1[1][2] = v1[n][n] = v2[n][n] = 1;

    REP1 (i, n) {
        if (!v1[i][2]) {
            bool ret = qry(i-1, 1, i, 2);
            g[0][i][2] = g[0][i-1][1] ^ ret ^ 1;
            g[1][i][2] = g[1][i-1][1] ^ ret ^ 1;
        }
        if (i > 1) {
            bool ret = qry(i-1, 2, i, 3);
            g[0][i][3] = g[0][i-1][2] ^ ret ^ 1;
            g[1][i][3] = g[1][i-1][2] ^ ret ^ 1;
        } else {
            bool ret = qry(i, 1, i, 3);
            g[0][i][3] = g[0][i][1] ^ ret ^ 1;
            g[1][i][3] = g[1][i][1] ^ ret ^ 1;
        }

        if (!v1[i][1]) {
            bool ret = qry(i, 1, i, 3);
            g[0][i][1] = g[0][i][3] ^ ret ^ 1;
            g[1][i][1] = g[1][i][3] ^ ret ^ 1;
        }
        for (int j=4; j<=n; j++) {
            if (!v1[i][j]) {
                bool ret = qry(i, j-2, i, j);
                g[0][i][j] = g[0][i][j-2] ^ ret ^ 1;
                g[1][i][j] = g[1][i][j-2] ^ ret ^ 1;
            }
        }
    }

    REP1 (i, n) {
        pary(g[0][i] + 1, g[0][i] + 1 + n);
    }

    REP1 (i, n) {
        pary(g[1][i] + 1, g[1][i] + 1 + n);
    }
    REP1 (xa, n) {
        REP1 (ya, n) {
            REP1 (xb, n) {
                REP1 (yb, n) {
                    if (xa + ya + 2 <= xb + yb && xa <= xb && ya <= yb) {
                        if (solve(0, xa, ya, xb, yb) != solve(1, xa, ya, xb, yb)) {
                            if (qry(xa, ya, xb, yb) == solve(0 , xa, ya, xb, yb)) {
                                ans(0);
                            } else {
                                ans(1);
                            }
                            return 0;
                        }
                    }
                }
            } 
        }
    }

    debug(solve(0, 1, 1, 2, 3), solve(1, 1, 1, 2, 3));
    debug("GG");
    return 0;
}
