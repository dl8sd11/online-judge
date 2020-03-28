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

const int MAXN = 200005;
const ll MOD = 1000000007;

string str;
int n, m;
vector<int> edge[MAXN];
int cnt[MAXN][2], sz;
bool B[MAXN];

bool vis[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    cin >> str;
    REP1 (i, n) {
        B[i] = str[i-1] == 'B';
    }
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
        cnt[u][B[v]]++;
        cnt[v][B[u]]++;
    }

    sz = n;

    vector<int> stk;
    REP1 (i, n) {
        if (cnt[i][0] == 0 || cnt[i][1] == 0) {
            stk.eb(i);
            vis[i] = true;
        }
    }

    while (stk.size()) {
        sz--;
        int nd = stk.back();
        stk.pop_back();

        for (auto v : edge[nd]) {
            cnt[v][B[nd]]--;
            if (!vis[v] && (cnt[v][0] == 0 || cnt[v][1] == 0)) {
                stk.eb(v);
                vis[v] = true;
            }
        }
    }

    debug(sz);
    assert(sz != 1);

    cout << (sz > 0 ? "Yes" : "No") << endl;

    #ifdef tmd

    REP1 (i, n) {
        if (!vis[i]) {
            debug(i, B[i]);
        }
    }

    #endif // tmd
}
