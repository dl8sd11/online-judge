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

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, m;
bool dired[MAXN];
int G[MAXN];

vector<int> edge[MAXN], tree[MAXN];
vector<int> seq;

int cnt[MAXN];

bool vis[MAXN];
void span (int nd, int par) {
    vis[nd] = true;
    for (auto v : edge[nd]) {
        int u = G[v] ^ nd;
        if (!vis[u]) {
            tree[nd].eb(u);
            span(u, nd);
        }
    }
    seq.eb(nd);
}


/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        G[i] = u ^ v;

        edge[u].eb(i);
        edge[v].eb(i);
    }

    if (m & 1) {
        cout << -1 << endl;
    } else {
        span(1, -1);

        for (auto v : seq) {
            for (auto u : edge[v]) {
                if (!dired[u]) {
                    if (cnt[v] & 1) {
                        cout << v << " " << (G[u]^v) << endl;
                        cnt[v]++;
                    } else {
                        cout << (G[u]^v) << " " << v << endl;
                        cnt[G[u]^v]++;
                    }
                }
                dired[u] = true;
            }
        }
    }
}
