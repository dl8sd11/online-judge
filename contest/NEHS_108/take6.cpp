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
#define X first
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

const int MAXN = 100005;
const ll MOD = 1000000007;
int head[105] = {-1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 3, 5, 1, 1, 1, 2, 1, 1, 1, 1, 3, 1, 5,\
 1, 1, 2, 1, 1, 1, 1, 3, 1, 1, 5, 1, 2, 1, 1, 1, 1, 3, 1, 1, 1, 5, 2, 1, 1, 1, 1, 3, 1,\
 1, 1, 1, 7, 1, 1, 1, 1, 3, 1, 1, 1, 1, 2, 5, 1, 1, 1, 3, 1, 1, 1, 1, 2, 1, 5, 1, 1, 3,\
 1, 1, 1, 1, 2, 1, 1, 5, 1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 5, 3, 1, 1, 1, 1};
 
int n, k;
int hd[12][12];
pii ans[12];
int cur[12];
vector<pii> rd;

struct TB {
	int lst, sum, cnt;
	
	void insert (int id) {
		sum += head[id];
		cnt++;
		lst = id;
	}
	
	void reset () {
		lst = 0;
		cnt = 0;
		sum = 0;
	}
} tb[4]; 

void dfs (int idx) {
	if (idx == SZ(rd)) {
		REP (i, n) {
			ans[i].X = min(ans[i].X, cur[i]);
			ans[i].Y = max(ans[i].Y, cur[i]);
		}
	} else {
		TB ttb[4];
		int tcur[12];
		REP (i, 4) {
			ttb[i] = tb[i];
		}
		REP (i, n) {
			tcur[i] = cur[i];
		}
		
		int bst = -1;
		REP (i, 4) {
			if (tb[i].lst < rd[idx].X) {
				if (bst == -1 || tb[bst].lst < tb[i].lst) {
					bst = i;
				}
			}
		}
		debug(bst);
		
		if (bst == -1) {
			int org = cur[rd[idx].Y];
			REP (i, 4) {
				REP (j, 4) {
					tb[j] = ttb[j];
				}
				cur[rd[idx].Y] = org + tb[i].sum;
				tb[i].reset();
				tb[i].insert(rd[idx].X);
				dfs(idx+1);
			}
		} else {
			if (tb[bst].cnt < 5) {
				tb[bst].insert(rd[idx].X);
			} else {
				cur[rd[idx].Y] += tb[bst].sum;
				tb[bst].reset();
				tb[bst].insert(rd[idx].X);
			}
			dfs(idx+1);
		}
		
		
		REP (i, n) {
			cur[i] = tcur[i];
		}		
		REP (i, 4) {
			tb[i] = ttb[i];
		}
	}
	
}
int main () {
	IOS();
	
	cin >> n >> k;
	REP (i, n) {
		REP (j, k) {
			cin >> hd[i][j];
		}
		ans[i] = pii(1000, -1000);
	}
	
	REP (i, 4) {
		int d;
		cin >> d;
		tb[i].reset();
		tb[i].insert(d);
	}
	
	REP (t, k) {
		vector<pii> cd;
		REP (i, n) {
			cd.eb(hd[i][t], i);
		}
		sort(cd.begin(), cd.end());
		for (auto d : cd) {
			rd.eb(d);
		}
	}
	
	dfs(0);
	
	REP (i, n) {
		cout << ans[i].X << " " << ans[i].Y << endl;
	}

	return 0;
}

