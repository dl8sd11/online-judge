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
const int MAXLG = __lg(MAXN) + 2;
const ll MOD = 1000000007;

int bit[MAXN*2];

void bitA (int x, int v) {
    for (x++; x<MAXN*2; x+=-x&x) {
        bit[x] += v;
    }
}

int bitQ (int x) {\
    int ret = 0;
    for (x++; x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int n;
vector<int> edge[MAXN];


int in[MAXN], out[MAXN], tme, anc[MAXLG][MAXN], dep[MAXN];
void dfs (int nd, int par) {
    in[nd] = tme++;
    anc[0][nd] = par;
    dep[nd] = dep[par] + 1;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
        }
    }
    out[nd] = tme++;
}

int kth (int v, int k) {
    for (int i=0; i<MAXLG; i++) {
        if ((k>>i) & 1) {
            v = anc[i][v];
        }
    }
    return v;
}

int rootSum (int v) {
    return bitQ(in[v]);
}

bool on[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    int q;
    cin >> n >> q;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs(1, 0);
    for (int i=1; i<MAXLG; i++) {
        for (int j=1; j<=n; j++) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }

    while (q--) {
        int cmd, v;
        cin >> cmd >> v;
        if (cmd) { // query
            if (rootSum(v) == 0) {
                cout << -1 << endl;
            } else {
                int l = 0, r = dep[v];

                while (l < r - 1) {
                    int m = (l + r) >> 1;
                    int mid = kth(v, dep[v]-m);
//                    debug(v, l, r, m, mid, rootSum(mid));
                    if (rootSum(mid) == 0) {
                        l = m;
                    } else {
                        r = m;
                    }
                }
                cout << kth(v, dep[v]-r) << endl;
            }
        } else {
            if (on[v]) {
                bitA(in[v], -1);
                bitA(out[v], 1);
            } else {
                bitA(in[v], 1);
                bitA(out[v], -1);
            }
            on[v] ^= 1;
        }
    }
}
