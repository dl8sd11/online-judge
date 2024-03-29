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


const int MAXN = 2003;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, q;

ll di[MAXN][MAXN], hr[MAXN][MAXN], ans[MAXN][MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q;
    REP (i, q) {
        int r, c, l, s;
        cin >> r >> c >> l >> s;
        hr[r][c] += s;
        hr[r+l][c] -= s;
        di[r][c+1] -= s;
        di[r+l][c+l+1] += s;
    }

    REP (i, MAXN) {
        REP (j, MAXN) {
            if (i > 0) {
                hr[i][j] += hr[i-1][j];
                if (j > 0) {
                    di[i][j] += di[i-1][j-1];
                }
            }
        }
    }

    REP1 (i, n) {
        ll sum = 0;
        REP1 (j, n) {
            sum += hr[i][j] + di[i][j];
            cout << sum << " \n"[j==n];
        }
    }
}
