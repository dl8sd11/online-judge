#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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

const int MAXN = 152;
const ll MOD = 1000000007;

int h, w, sx, sy, a[MAXN][MAXN];

vector<pair<int,ll> > edge[MAXN*MAXN*2];

int id (int x, int y, int pa) {
    return (x*w + y) * 2 + pa;
}

bool ban (int x, int y) {
    return x == sx && y == sy;
}

bool valid (int x, int y) {
    return 0 <= x && x < h && 0 <= y && y < w;
}

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void build () {
    REP (i, h) {
        REP (j, w) {
            if (ban(i, j)) {
                continue;
            }
            for (int k=0; k<4; k++) {
                int nx = i + dx[k];
                int ny = j + dy[k];

                if (valid(nx, ny) && !ban(nx, ny)) {
                    bool c1 = (j == sy) && (i < sx) && (k == 1);
                    bool c2 = (ny == sy) && (nx < sx) && (k == 3);
                    bool cross = c1 | c2;

                    REP (p, 2) {
                        edge[id(i,j,p)].emplace_back(id(nx,ny,p^cross), a[nx][ny]);
                    }
                }
            }
        }
    }
}

ll dis[MAXN*MAXN*2];
bool vis[MAXN*MAXN*2];
typedef pair<ll,int> pli;

ll dijkstra (int ix, int iy) {
    priority_queue<pli,vector<pli>,greater<pli> > pq;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));

    int sid = id(ix, iy, 0);
    dis[sid] = 0;
    pq.emplace(0, sid);

    while (pq.size()) {
        int pt = pq.top().second;
        pq.pop();
        if (vis[pt]) {
            continue;
        }
        vis[pt] = true;

        for (auto v : edge[pt]) {
            if (dis[v.first] > dis[pt] + v.second) {
                dis[v.first] = dis[pt] + v.second;
                pq.emplace(dis[v.first], v.first);
            }
        }
    }

    return dis[id(ix, iy, 1)];
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> h >> w >> sx >> sy;

    sx--, sy--;
    REP (i, h) {
        REP (j, w) {
            cin >> a[i][j];
        }
    }

    build();

    ll ans = 0x3f3f3f3f3f3f3f3f;
    for (int i=0; i<sx; i++) {
        ans = min(ans, dijkstra(i, sy));
    }

    cout << ans << endl;
}
