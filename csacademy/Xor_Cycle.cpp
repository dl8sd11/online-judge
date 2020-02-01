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
const int MAXD = 60;
const ll MOD = 1000000007;

int n, m;

typedef pair<int,ll> pil;
vector<pil> edge[MAXN];

vector<ll> vec;
ll pre[MAXN];
bool vis[MAXN];

ll basis[MAXN];

void ins (ll vec) {
    for (int i=MAXD; i>=0; i--) {
        if ((vec >> i) & 1) {
            if (basis[i] == 0) {
                basis[i] = vec;
                break;
            } else {
                vec ^= basis[i];
            }
        }
    }
}

void dfs (int nd, int par) {
    vis[nd] = true;

    for (auto v : edge[nd]) {
        int t = v.first;
        if (vis[t]) {
            ins(pre[nd]^pre[t]^v.second);
        } else {
            pre[t] = pre[nd] ^ v.second;
            dfs(t, nd);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int u, v;
        ll w;
        cin >> u >> v >> w;

        edge[u].emplace_back(v, w);
        edge[v].emplace_back(u, w);
    }

    dfs(1, -1);
    ll ans = 0;

    for (int i=MAXD; i>=0; i--) {
        if (((ans >> i) & 1) == 0) {
            ans ^= basis[i];
        }
    }

    cout << ans << endl;
}
