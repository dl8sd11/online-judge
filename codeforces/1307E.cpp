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

int n, m, s[MAXN];
int hun[MAXN][MAXN];
int f[MAXN], h[MAXN];
int pre[MAXN][MAXN], suf[MAXN][MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP1 (i, n) {
        cin >> s[i];
        pre[s[i]][i]++;
        suf[s[i]][i]++;
    }
    REP1 (j, n) {
        REP1 (i, n) {
            pre[j][i] += pre[j][i-1];
        }
        for (int i=n;i >=1; i--) {
            suf[j][i] += suf[j][i+1];
        }
    }

    REP (i, m) {
        int F, H;
        cin >> F >> H;
        f[i] = F;
        h[i] = H;
        hun[F][H]++;
    }
    REP1 (i, n) {
        REP1 (j, n) {
            hun[i][j] += hun[i][j-1];
        }
    }

    ll ans = 0;
    REP (i, m) {
        if (pre[f[i]][n] >= h[i]) {

            int j, cnt = 0;
            for (j=1; j<=n; j++) {
                cnt += s[j] == f[i];
                if (cnt == h[i]) {
                    break;
                }
            }



        }
    }
}
