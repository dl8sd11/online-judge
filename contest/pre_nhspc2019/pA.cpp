#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("03","unroll-loops")
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define MEM(a,b) memset(a,(b),sizeof(a))
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d: (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
template<typename T> ostream &operator << (ostream &os, const pair<T,T> &p){return os<<"("<<p.first<<","<<p.second<<")";}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 102;


int t, n, m;
int a[MAXN][MAXN];

struct Data {
    bool dir;
    pii px, py;
};
map<int,bool> dp[2]; // (a,b) and (c,d)

int hashData (pii px, pii py) {
    return (px.first*MAXN*MAXN*MAXN+px.second*MAXN*MAXN+py.first*MAXN+py.second);
}

bool valid (pii pos) {
    return pos.first >= 0 && pos.first < n && pos.second >= 0 && pos.second < m;
}

int dx[2][2] = {{-1,0},{1, 0}};
int dy[2][2] = {{0,-1},{0, 1}};
bool solve (bool dir, pii px, pii py) {
    int cur = hashData(px, py);

    if (dp[dir].count(cur)) {
        return dp[dir][cur];
    }
    if (!valid(px) || !valid(py)) {
        return dp[dir][cur] = false;
    }
    if (px == py) {
        return dp[dir][cur] = true;
    }
    if (a[px.first][px.second] != a[py.first][py.second]) {
        return dp[dir][cur] = false;
    }
    bool &ret = dp[dir][cur];
    ret = false;

    REP (xid, 2) {
        REP (yid, 2) {
            pii nx = px, ny = py;
            nx.first += dx[dir][xid];
            nx.second += dy[dir][xid];

            ny.first += dx[dir][yid];
            ny.second += dy[dir][yid];
            ret |= solve(dir, nx, ny);
        }
    }

    return ret;

}

int main () {
    IOS();
    cin >> t;
    while (t--) {
#ifdef tmd
        n = 100, m = 100;
#else
        cin >> n >> m;
#endif // tmd

        vector<pii> pos[MAXN*2];
        REP (i, n) {
            REP (j, m) {
#ifdef tmd
                a[i][j] = rand() % 100;
#else
                cin >> a[i][j];
#endif // tmd
                pos[i+j].emplace_back(i, j);
            }
        }

        bool ans = false;
        dp[0].clear();
        dp[1].clear();
        REP (dis, n+m-2) {
            REP (i, SZ(pos[dis])) {
                REP (j, i) {
                    ans |= solve(0, pos[dis][i], pos[dis][j]) && solve(1, pos[dis][i], pos[dis][j]);
                    if (ans) {
                        debug(pos[dis][i], pos[dis][j]);
                    }
                }
                if (ans) {
                    break;
                }
            }
            if (ans) {
                break;
            }
        }

        cout << (ans ? "Yes" : "No") << endl;

    }
}
