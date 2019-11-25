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
const int MAXC = 51;
const ll MOD = 1000000007;

struct Plan {
    int cores, freq, price;
    bool operator < (const Plan &oth) const {
        if (freq == oth.freq) {
            return cores < oth.cores; // buy first
        } else {
            return freq > oth.freq;
        }
    }
} plans[MAXN*2];

int n, m;
ll dp[2][MAXN*MAXC]; // dp[N][M] maximal price with M cores left
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> plans[i].cores >> plans[i].freq >> plans[i].price;
        plans[i].price *= -1;
        plans[i].cores *= -1;
    }
    cin >> m;
    for (int i=n; i<n+m; i++) {
        cin >> plans[i].cores >> plans[i].freq >> plans[i].price;
    }
    sort(plans, plans+n+m);

    for (int i=0; i<2; i++) {
        for (int j=0; j<MAXN*MAXC; j++) {
            dp[i][j] = -MOD*MOD;
        }
    }
    dp[1][0] = 0;

    ll ans = 0;
    for (int i=0; i<n+m; i++) {
        bool c = i&1;
        bool p = (i&1) ^ 1;
        debug(plans[i].cores, plans[i].freq, plans[i].price);
        for (int j=0; j<MAXN*MAXC; j++) {
            dp[c][j] = dp[p][j];
            if (plans[i].cores+j >= 0 && plans[i].cores+j<MAXN*MAXC) {
                dp[c][j] = max(dp[c][j], dp[p][plans[i].cores+j]+plans[i].price);
            }
            ans = max(ans, dp[c][j]);
        }
    }

    cout << ans << endl;
}
/*
4
4 2200 700
2 1800 10
20 2550 9999
4 2000 750
3
1 1500 300
6 1900 1500
3 2400 4550
*/
