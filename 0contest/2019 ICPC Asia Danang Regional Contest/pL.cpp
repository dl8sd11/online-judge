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

const int MAXN = 102;
const ll MOD = 1000000007;

int n, k, a[MAXN][MAXN];
bool used[MAXN];

vector<int> edge[MAXN];

bool vis[MAXN];
int yp[MAXN], xp[MAXN];

bool dfs (int x) {
    if (vis[x]) {
        return false;
    }
    vis[x] = true;

    for (auto v : edge[x]) {
        if (yp[v] == -1 || dfs(yp[v])) {
            yp[v] = x;
            return true;
        }
    }
    return false;
}

void build (int x) {
    REP (i, n) {
        REP (j, n) {
            if (a[i][j] == 0) {
                edge[i].eb(j);
            }
        }
    }

    int cnt = 0;
    memset(yp, -1, sizeof(yp));
    memset(xp, -1, sizeof(yp));

    REP (i, n) {
        for (auto v : edge[i]) {
            if (yp[v] == -1) {
                yp[v] = i;
                xp[i] = v;
                cnt++;
                break;
            }
        }
    }

    REP (i, n) {
        if (xp[i] == -1) {
            memset(vis, 0, sizeof(vis));
            if (dfs(i)) {
                cnt++;
            }
        }
    }

    assert(cnt == n);
    REP (i, n) {
        edge[i].clear();
        a[yp[i]][i] = x;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP (i, n) {
        REP (j, n) {
            #ifdef tmdd
            a[i][j] = 0;
            #else
            cin >> a[i][j];
            #endif // tmd
            used[a[i][j]] = true;
        }
    }

    REP1 (i, n) {
        if (!used[i]) {
//            debug(i);
            build(i);
        }
    }

    cout << "YES" << endl;
    REP (i, n) {
        REP (j, n) {
            cout << a[i][j] << " \n"[j==n-1];
        }
    }
}
