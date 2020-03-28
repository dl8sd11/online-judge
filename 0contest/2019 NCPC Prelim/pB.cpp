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

const int MAXN = 36;
const ll MOD = 1000000007;

int t, n, d[MAXN], dp[MAXN][2];
vector<int> edge[MAXN];

void dfs (int nd, int par) {
    vector<int> dl;

    int sum = 0;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
            dl.eb(dp[v][1] - dp[v][0]);
            sum += dp[v][0];
        }
    }
    sort(ALL(dl));
//    debug(sum, dl);


    dp[nd][1] = sum + 1;
    int tmp = sum;
    if (SZ(dl)>=d[nd]) {
        REP (i, d[nd]) {
            tmp += dl[i];
        }
        dp[nd][1] = min(dp[nd][1], tmp);
    }

    int tmp2 = sum;
    REP (i, d[nd]-1) {
        tmp2 += dl[i];
    }
    dp[nd][0] = min({tmp2, dp[nd][1]});

//    debug(nd, dp[nd][0], dp[nd][1]);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n;
        REP (i, n) {
            cin >> d[i];
            edge[i].clear();
        }

        int p;
        cin >> p;
        assert(p == n-1);

        REP (i, p) {
            int u, v;
            cin >> u >> v;
            edge[u].eb(v);
            edge[v].eb(u);
        }

        dfs(0, -1);

        cout << dp[0][1] << endl;
    }

}

/*
5
6 2 2 1 2 1 1
5
0 1
5 3
0 3
4 1
2 3
3 1 1 1
2
0 1
0 2
5 1 2 1 1 1
4
0 2
2 4
2 1
1 3
5 1 2 2 1 1
4
0 2
2 4
2 1
1 3
8 3 2 2 1 1 1 1 1
7
0 1
0 2
0 7
1 3
1 4
2 5
2 6
*/
