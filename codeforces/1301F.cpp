#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
A#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1003;
const ll MOD = 1000000007;

int n, m, k;
int c[MAXN][MAXN];
vector<pair<int,int> > p[41];

bool vis[41];
int dis[41][MAXN][MAXN];

bool valid (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

void build (int color) {
    queue<pair<int,int> > bfs;
    for (auto v : p[color]) {
        bfs.emplace(v);
        dis[color][v.X][v.Y] = 0;
    }
    memset(vis, 0, sizeof(vis));
    vis[color] = true;

    while (bfs.size()) {
        auto cur = bfs.front();
        bfs.pop();

        int cdis = dis[color][cur.X][cur.Y];
        int cc = c[cur.X][cur.Y];

        if (!vis[cc]) {
            for (auto v : p[cc]) {
                if (dis[color][v.X][v.Y] == 0x3f3f3f3f) {
                    bfs.emplace(v);
                    dis[color][v.X][v.Y] = cdis + 1;
                }
            }
        }
        vis[cc] = true;

        int dx[] = {0, 1, 0, -1};
        int dy[] = {1, 0, -1, 0};

        REP (d, 4) {
            int nx = cur.X + dx[d];
            int ny = cur.Y + dy[d];

            if (valid(nx, ny) && dis[color][nx][ny] == 0x3f3f3f3f) {
                bfs.emplace(nx, ny);
                dis[color][nx][ny] = cdis + 1;
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    memset(dis, 0x3f, sizeof(dis));
    cin >> n >> m >> k;

    REP1 (i, n) {
        REP1 (j, m) {
            cin >> c[i][j];
            p[c[i][j]].eb(i, j);
        }
    }

    REP1 (i, k) {
        build(i);
    }

    int q;
    cin >> q;

    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        int ans = abs(r1-r2) + abs(c1-c2);

        REP1 (i, k) {
            ans = min(ans, dis[i][r1][c1] + dis[i][r2][c2] + 1);
        }

        cout << ans << endl;
    }
}
