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

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, l, q, par[MAXN], val[MAXN], dsz[MAXN];
bool up[MAXN];

vector<int> child[MAXN];

int ans;
ll sum;
void dfs (int nd) {
    if (val[nd] == 1) {
        up[nd] = true;
    } else {
        up[nd] = up[par[nd]];
    }

    if (val[nd] == l) {
        dsz[nd] = 1;
    }
    for (auto v : child[nd]) {
        dfs(v);
        if (val[v] == val[nd] + 1) {
            dsz[nd] += dsz[v];
        }
    }
    if (val[nd] == 1) {
        ans += dsz[nd];
    }
}

void chg (int nd, int x) {
    if (up[nd]) {
        ans -= dsz[nd];
    }
    val[nd] = x;


    up[nd] = false;
    if (val[nd] == 1) {
        up[nd] = true;
    } else {
        up[nd] = up[par[nd]];
    }

    if (val[nd] == l) {
        dsz[nd] = 1;
    } else {
        dsz[nd] = 0;
    }

    for (auto v : child[nd]) {
        if (val[v] == val[nd] + 1) {
            dsz[nd] += dsz[v];
        }
    }
    if (val[nd] == 1) {
        ans += dsz[nd];
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> l >> q;
    REP1 (i, n-1) {
        cin >> par[i];
        child[par[i]].emplace_back(i);
    }
    REP (i, n) {
        cin >> val[i];
    }

    dfs(0);
    debug(ans);

    REP (i, q) {
        int d;
        cin >> d;

        chg(i%n, d);

        sum += i * ans % MOD;
        sum %= MOD;
        debug(ans);
    }

    cout << sum << endl;
}
