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

const int MAXN = 5003;
const ll MOD = 1000000007;

int n, m, k;
double dis[MAXN][MAXN];
pii pts[MAXN];
double span[MAXN];
bool vis[MAXN];

double SQ (int x) {
    return (double)x * x;
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> k;
    REP (i, k) {
        cin >> pts[i].X >> pts[i].Y;
    }

    REP (i, k) {
        REP (j, k) {
            dis[i][j] = sqrt(SQ(pts[i].X-pts[j].X) + SQ(pts[i].Y-pts[j].Y));
        }
        dis[i][k] = dis[k][i] = pts[i].Y;
        dis[i][k+1] = dis[k+1][i] = m - pts[i].Y;
    }
    dis[k][k+1] = m;
    dis[k+1][k] = m;

    debug("built");

    fill(span, span+MAXN, 1e7);
    span[k] = 0;

    while (true) {

        int bst = -1;

        for (int i=0; i<k+2; i++) {
            if (!vis[i]) {
                if (bst == -1) {
                    bst = i;
                } else if (span[i] < span[bst]) {
                    bst = i;
                }
            }
        }
        vis[bst] = true;

        debug(bst);
        if (bst == k+1) {
            break;
        }

        for (int i=0; i<k+2; i++) {
            span[i] = min(span[i], max(span[bst],dis[bst][i]));
        }
    }

    cout << fixed << setprecision(10) << span[k+1]/2 << endl;
}
