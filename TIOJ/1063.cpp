#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
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

const int MAXN = 205;
const ll MOD = 1000000007;

int n, m;
bool bk[MAXN][MAXN];
int h[MAXN][MAXN];
int l[MAXN], r[MAXN];
int lw[MAXN];
int lcnt, rcnt;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP1 (i, n) {
        REP1 (j, m) {
            cin >> bk[i][j];
            h[i][j] = bk[i][j] ? h[i-1][j] + 1 : 0;
        }
    }

    int ans = 0;
    REP1 (i, n) {
        lcnt = 0, rcnt = 0;
        l[lcnt++] = 0;
        for (int j=1; j<=m; ++j) {
            while (lcnt && h[i][l[lcnt-1]] >= h[i][j]) {
                --lcnt;
            }

            lw[j] = lcnt ? l[lcnt-1] : 0;
            l[lcnt++] = j;
        }

        r[rcnt++] = m+1;
        for (int j=m; j>=1; --j) {
            while (rcnt && h[i][r[rcnt-1]] >= h[i][j]) {
                --rcnt;
            }

            if (h[i][j]) {
                ans = max(ans, (r[rcnt-1]-lw[j]-1) * h[i][j]);
            }
            r[rcnt++] = j;
        }
    }

    cout << ans << endl;
}
