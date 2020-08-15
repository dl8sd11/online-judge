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

const int MAXN = 202;
const ll MOD = 1000000007;
const ll INF = 1e18 + 18;

int s, m, q;

ll dp[MAXN][MAXN][MAXN];

void trim (ll &x) {
    if (x >= INF) {
        x = INF;
    }
}

void build () {
    dp[0][0][0] = 1;

    int tenr = 1; // remainder of ten pows
    for (int i=1; i<MAXN; i++) {
        for (int j=0; j<m; j++) {
            for (int k=0; k<=s; k++) {
                for (int d=0;d<10;d++) {
                    int r = j - tenr * d % m;
                    r = (r % m + m) % m; // normalize
                    if (k >= d) {
                        dp[i][j][k] += dp[i-1][r][k-d];
                        trim(dp[i][j][k]);
                    }
                }
            }
        }
        tenr = tenr * 10 % m;
    }
}

void solve (ll k) {
    string res;
    int rem = 0;
    int sum = 0;

    int tenr[MAXN] = {};
    tenr[0] = 1;
    for (int i=1; i<MAXN; i++) {
        tenr[i] = tenr[i-1] * 10 % m;
    }

    for (int i=200; i>0; i--) {
        int sel = -1;
        for (int j=0; j<10; j++) {
            int rr = (rem + j*tenr[i-1]) % m;
            // TODO check s - sum - j < 0
            if (s-sum-j >=0 && dp[i-1][(m-rr)%m][s-sum-j] >= k) {
                sel = j;
                break;
            }
            if (s-sum-j >= 0) {
                k -= dp[i-1][(m-rr)%m][s-sum-j];
            }
        }
        if (sel == -1) {
            debug(res);
            cout << "NIE" << endl;
            return;
        }
        rem = (rem + sel*tenr[i-1]) % m;
        sum += sel;
        debug(sel, rem, sum);
        debug(dp[i-1][rem][s-sum]);
        if (sel != 0 || !res.empty()) {
            res += char(sel + '0');
        }
    }
    cout << res << endl;

}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> s >> m >> q;
    build();

    while (q--) {
        ll k;
        cin >> k;
        solve(k);
    }

}

