#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define pb push_back
#define ALL(i) i.begin(),i.end()
#define X first
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

const int MAXN = 200005;
const int MAXLG = __lg(MAXN) + 3;
const ll MOD = 1000000007;


int n, m;
vector<pii> graph[MAXN];

int low[MAXN], dfn[MAXN], dfs_clock = 0;
bool is_cut[MAXN];

int asn[MAXN], res;
vector<int> g[MAXN];
void bf (int idx) {
    if (idx == m) {
        bool flag = true;
        for (int i=1; i<=n; ++i) {
            int sum = 0;
            for (auto v : g[i]) {
                sum += asn[v];
            }
            flag &= (sum % 5 == 0);
        }
        res += flag;
    } else {
        for (int i=0; i<5; i++) {
            asn[idx] = i;
            bf(idx+1);
        }
    }

}
struct BCC {
	vector<int> vert;
	vector<int> edgs;
};
vector<BCC> bcc;

vector<int> stk,estk;

bool vis[MAXN];
void dfs_bcc (int nd, int pa) {
	vis[nd] = true;
    low[nd] = dfn[nd] = dfs_clock++;
    stk.eb(nd);
    debug(nd, pa);
    for (auto ed : graph[nd]) {
		int v = ed.X;

        if (v != pa) {
			if (dfn[v] != -1 && dfn[v] >= dfn[pa]) { // forward edge
				continue;
			}
			estk.eb(ed.Y);
			int cur = ed.Y;
            if (dfn[v] == -1) { // tree edge
                dfs_bcc(v, nd);
                low[nd] = min(low[nd], low[v]);
                if (low[v] >= dfn[nd]) {
                    debug(nd, pa, v, low[v], dfn[nd]);
                    is_cut[nd] |= (dfn[nd] > 0 || dfn[v] > 1); // not root or > 1 child
                    vector<int> new_comp = {nd};
                    while (new_comp.back() != v) {
                        new_comp.eb(stk.back());
                        stk.pop_back();
                    }

					vector<int> nw_edg;
					while (true) {
						nw_edg.eb(estk.back());
						estk.pop_back();
						if (nw_edg.back() == cur) {
							break;
						}
					}
                    bcc.pb({new_comp, nw_edg});
                }
            } else { // back edge
                low[nd] = min(low[nd], dfn[v]);
            }


        }
    }
}


/*********************GoodLuck***********************/
int main () {
    IOS();
	int t;
	cin >> t;

	while (t--) {

		cin >> n >> m;
		for (int i=0; i<m; i++) {
			int u, v;
			cin >> u >> v;
			graph[u].eb(v, i);
			graph[v].eb(u, i);
			g[u].eb(i);
			g[v].eb(i);
		}

		dfs_clock = 0;
		
		for (int i=1; i<=n; i++) {
			low[i] = 0;
			is_cut[i] = 0;
			dfn[i] = -1;

		}
		bcc.clear();
		debug(stk, estk);
		stk.clear();
		estk.clear();
		assert(stk.empty());
		assert(estk.empty());

		debug("test");
	
		for (int i=1; i<=n; i++) {
			if (!vis[i]) {
				dfs_bcc (1, 0);
			}
		}
		
		int pw = 0;
		for (auto cc : bcc) {
			debug(cc.vert, cc.edgs);
			int v = SZ(cc.vert);
			int e = SZ(cc.edgs);

			if (v == e && v % 2 == 0) {
				pw++;
			} else {
				pw += max(0, e-v);
			}
		}

		ll ans = 1;
		for (int i=0; i<pw; i++) {
			ans = ans * 5 % 998244353;
		}

		#ifdef tmd

		res = 0;
		bf(0);
		debug(res, ans);

		#endif

		cout << ans << endl;

		for (int i=1; i<=n; i++) {
			graph[i].clear();
		}
	}
}

/*
9 14
1 2
1 3
3 4
3 5
4 5
4 7
5 6
5 7
6 7
1 8
1 9
2 9
2 8
9 8
1
4 9

*/
