#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<(n);i++)
#define REP1(i,n) for(int i=1;i<=(n);i++)
#define SZ(i) int((i).size())
#define MEM(a,b) memset((a),(b),sizeof(a))
#define eb emplace_back
#define pb push_back
#define ALL(i) (i).begin(),(i).end()
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&X){cerr<<X<<endl;}
template<typename T, typename ...S> void _do(T &&x, S&&...y){cerr<<x<<",";_do(y...);}
template<typename IT> ostream& __printRng (ostream& os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        cout << (it==bg?"":",") << *it;
    }
    os << "}";
    return os;
}
template<typename T> ostream& operator << (ostream& os, const vector<T> &vec) {
    return __printRng(os, vec.begin(), vec.end());
}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 100005;

int n, a[MAXN];
vector<int> edge[MAXN];

ll ans;
bool vlock[MAXN];
int sz[MAXN];

void buildSz (int nd, int par) {
    sz[nd] = 1;
    for (auto v : edge[nd]) {
        if (v != par && !vlock[v]) {
            buildSz(v, nd);
            sz[nd] += sz[v];
        }
    }
}

int rootSz;
pair<int,int> minSub (int nd, int par) {
    pair<int,int> ret = {MAXN, -1};
    int mx = rootSz - sz[nd];
    for (auto v : edge[nd]) {
        if (v != par && !vlock[v]) {
            ret = min(ret, minSub(v, nd));
            mx = max(mx, sz[v]);
        }
    }
    return min(ret, {mx, nd});
}

int getCentroid (int nd) {
    buildSz(nd, nd);
    rootSz = sz[nd];
    return minSub(nd, nd).second;
}

const int MAXC = 20;

struct Subtree {
    int cnt[2][MAXC];

    Subtree () {
        memset(cnt, 0, sizeof(cnt));
    }

    void operator += (const Subtree &oth) {
        REP (i, 2) {
            REP (j, MAXC) {
                cnt[i][j] += oth.cnt[i][j];
            }
        }
    }
};

void calc (int nd, int par, int cur, Subtree &dt) {
    cur ^= a[nd];
    REP (d, MAXC) {
        dt.cnt[(cur>>d) & 1][d]++;
    }
    for (auto v : edge[nd]) {
        if (v != par && !vlock[v]) {
            calc(v, nd, cur, dt);
        }
    }
}

void decomp (int nd) {
    int cen = getCentroid(nd);
    vlock[cen] = true;

    for (auto v : edge[cen]) {
        if (!vlock[v]) {
            decomp(v);
        }
    }

    Subtree sum;
    REP (d, MAXC) {
        sum.cnt[(a[cen]>>d) & 1][d]++;
    }

    ans += a[cen];
    for (auto v : edge[cen]) {
        if (!vlock[v]) {
            Subtree cur;
            calc(v, cen, a[cen], cur);

            REP (d, MAXC) {
                if (a[cen] & (1<<d)) {
                    ans += (1LL<<d) * cur.cnt[0][d] * sum.cnt[0][d];
                    ans += (1LL<<d) * cur.cnt[1][d] * sum.cnt[1][d];
                } else {
                    ans += (1LL<<d) * cur.cnt[0][d] * sum.cnt[1][d];
                    ans += (1LL<<d) * cur.cnt[1][d] * sum.cnt[0][d];
                }
            }

            sum += cur;
        }
    }

    vlock[cen] = false;
}

int main () {
    cin >> n;
    REP1 (i, n) {
        cin >> a[i];
    }
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    decomp(1);

    cout << ans << endl;
}
