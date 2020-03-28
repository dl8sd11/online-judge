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

const int MAXN = 500005;
const int MAXC = (1<<20) + 6;
const int MAXD = 11;

const ll MOD = 1000000007;

int n, d, a[MAXN], dp[MAXC][MAXD];
int rw[2][MAXD];

inline int add (int x, int y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
    return x;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> d;
    REP (i, n) {
        cin >> a[i];
    }
    sort(a, a+n);

    dp[0][0] = 1;

    int lim = 1;
    for (int i=0; i<n; i++) {
        while (lim <= a[i]) {
            lim <<= 1;
        }

        for (int msk=0; msk<lim; msk++) {
            if ((msk^a[i]) < msk) {

                for (int r=0; r<d; r++) {
                    rw[0][r] = dp[msk^a[i]][r];
                    rw[1][r] = dp[msk][r];
                }

                for (int r=0; r<d; r++) {
                    int prv = r ? r-1 : d-1;
                    dp[msk^a[i]][r] = add(rw[0][prv], rw[1][r]);
                    dp[msk][r] = add(rw[1][prv], rw[0][r]);
                }
            }
        }
    }

    int ans = dp[0][0];

    if (n % d == 0) {
        ans = ans ? ans-1 : MOD-1;
    }


    cout << ans << endl;


}
