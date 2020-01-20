#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define eb emplace_back
#define MEM(a,b) memset(a,(b),sizeof(a))
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif // tmd

const int INF = 0x3f3f3f3f;
const int MAXN = 102;

int n;
const int N = 100;
bool blk[MAXN][MAXN];
vector<int> edge[MAXN*MAXN];
int s, t;

int toID (int x, int y) {
    return x * N + y;
}

int dx[8] = {1,-1,-3,-3,-1,1,3,3};
int dy[8] = {3,3,1,-1,-3,-3,-1,1};
int bx[8] = {0,0,-1,-1,0,0,1,1};
int by[8] = {1,1,0,0,-1,-1,0,0};

bool valid (int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

int dis[MAXN*MAXN];
/*********Good***Luck*********/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        int x, y;
        cin >> x >> y;
        blk[x][y] = true;
    }
    {
        int sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;
        s = toID(sx, sy);
        t = toID(ex, ey);
    }

    REP (i, N) {
        REP (j, N) {
            if (blk[i][j]) {
                continue;
            }
            REP (d, 8) {
                int nx = i + dx[d];
                int ny = j + dy[d];
                int bbx = i + bx[d];
                int bby = j + by[d];

                if (valid(nx, ny) && !blk[nx][ny] && !blk[bbx][bby]) {
                    edge[toID(i, j)].emplace_back(toID(nx, ny));
                }
            }
        }
    }

    queue<int> bfs;
    bfs.emplace(s);
    memset(dis, INF, sizeof(dis));
    dis[s] = 0;
    while (bfs.size()) {
        int cur = bfs.front();
        bfs.pop();

        for (auto x : edge[cur]) {
            if (dis[x] == INF) {
                dis[x] = dis[cur] + 1;
                bfs.emplace(x);
            }
        }
    }

    if (dis[t] == INF) {
        cout << "impossible" << endl;
    } else {
        cout << dis[t] << endl;
    }

    return 0;
}
