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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1<<8;

const int rmask = MAXN-1;
int cnt[MAXN][MAXN][9];

int n, m;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n) {
        int a;
        cin >> a;
        int cur[17] = {};
        REP (l, MAXN) {
            int ld = __builtin_popcount(l^(a>>8));
            REP (b, 9) {
                cur[b+ld] += cnt[l][a&rmask][b];
            }
        }

        REP (i, m+1) {
            cout << cur[i] << " \n"[i==m];
        }

        REP (r, MAXN) {
            int rd = __builtin_popcount(r^(a&rmask));
            cnt[a>>8][r][rd]++;
        }
    }

}
