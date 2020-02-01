#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define ALL(i) i.begin(),i.end();
#define SZ(i) int(i.size())
#define MEM(i,n) memset(i, (n), sizeof(i))
#define X firsrt
#define Y second
#define eb emplace_back
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ", __PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif

const int MAXN = 1003;
const ll MOD = 1000000007;

int n, m, k;
bool g[MAXN][MAXN];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};
int toInt (int x, int y) {
	return x*m+y;
}
int valid(int x, int y) {
	return x>=0 && x<n && y>=0 && y <m;
}
vector<int> edge[MAXN*MAXN];
bool vis[MAXN*MAXN];
int dis[MAXN*MAXN];

struct Tran {
	int x, y, c;
} tran[100005];
int main () {
	IOS();

	cin >> n >> m >> k;
	REP (i, n) {
		REP (j, m) {
			char c;
			cin >> c;
			g[i][j] = c == '#';
		}
	}
	
	REP (i, n) {
		REP (j, m) {
			REP (d, 4) {
				int cx = i + dx[d];
				int cy = j + dy[d];
				if (valid(cx,cy) && !g[i][j] && !g[cx][cy]) {
					edge[toInt(i, j)].eb(toInt(cx, cy));
				}
			}
		}
	}
	REP (i, k) {
		cin >> tran[i].x >> tran[i].y >> tran[i].c;
	}
	
	int p, q;
	cin >> p >> q;
	
	MEM(dis, 0x3f3f3f3f);
	queue<int> bfs;
	bfs.emplace(toInt(p-1, q-1));
	vis[toInt(p-1, q-1)] = true;
	dis[toInt(p-1, q-1)] = 0;
	
	while (bfs.size()) {
		int cur = bfs.front();
		bfs.pop();
		
		for (auto v : edge[cur]) {
			if (!vis[v]) {
				vis[v] = true;
				dis[v] = dis[cur] + 1;
				bfs.emplace(v);
			}
		}
	}
	
#ifdef tmd
	REP (i, n) {
		REP (j, m) {
			cout << dis[toInt(i, j)] << " \n"[j==m-1];
		}
	}
#endif

	int ans = 0x3f3f3f3f;
	REP (i, k) {
		ans = min(ans, dis[toInt(tran[i].x-1, tran[i].y-1)] + tran[i].c);
	}
	
	cout << (ans >= 0x3f3f3f3f ? -1 : ans)<< endl;
	return 0;
}

