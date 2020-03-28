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

const int MAXN = 302;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, k, h[MAXN];
vector<int> H;

ll dp[MAXN][MAXN][MAXN]; // n, k, h
ll gr[MAXN][MAXN][MAXN], le[MAXN][MAXN][MAXN];

void build (int i, int j) {
    ll bst = INF;
    for (int l=0; l<SZ(H); l++) {
        bst = min(bst,dp[i][j][l]-H[l]);
        le[i][j][l] = bst;
    }
    bst = INF;
    for (int l=SZ(H)-1; l>=0; l--) {
        bst = min(bst, dp[i][j][l]);
        gr[i][j][l] = bst;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP (i, n) {
        cin >> h[i];
        H.eb(h[i]);
    }

    H.eb(0);
    sort(ALL(H));
    H.resize(unique(ALL(H))-H.begin());
    REP (i, n) {
        h[i] = lower_bound(ALL(H),h[i])-H.begin();
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] =0;

    for (int i=0; i<=n; i++) {
        for (int j=0; j<=k; j++) {
            build(i,j);
        }
    }

    ll res = INF;
    for (int i=1; i<=n; i++) {
        for (int j=0; j<=k; j++) {
            for (int l=0; l<SZ(H); l++) {
                ll bst = INF;
                if (l != h[i-1]) {
                    if (j > 0) {
                        bst = min(le[i-1][j-1][l]+H[l], gr[i-1][j-1][l]);
                    }
                } else {
                    bst = min(le[i-1][j][l]+H[l], gr[i-1][j][l]);
                }
                debug(i, j, l, bst);
                dp[i][j][l] = bst;
                if (i == n) {
                    res = min(res, dp[i][j][l]);
                }
            }
            build(i,j);
        }
    }

    cout << res << endl;


}
