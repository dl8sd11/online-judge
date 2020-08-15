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
const int MOD = 1000000007;

void sub (string &str) {
    int n = SZ(str);
    int lst = 0;
    for (int i=0; i<n; i++) {
        if (str[i] != '0') {
            lst = i;
        }
    }
    str[lst]--;
    for (int i=lst+1; i<n; i++) {
        str[i] = '9';
    }
}

void add (int &x, int y) {
    x = x + y >= MOD ? x + y - MOD : x + y;
}


int dp[MAXN][61][61][2], m, p10[MAXN];

int subm (int x, int y) {
    return x - y < 0 ? x - y + m : x - y;
}

void addm (int &x, int y) {
    x =  x + y >= m ? x + y - m : x + y;
}

int solve (const string &str) {
    int n = SZ(str);
    debug(str);

    REP (u, n+1) {
        REP (i, m) {
            REP (j, m) {
                REP (k, 2) {
                    dp[u][i][j][k] = 0;
                }
            }
        }
    }

    dp[n][0][0][0] = 1;
    for (int i=n-1; i>=0; i--) {
        for (int s=0; s<m; s++) {
            for (int r=0; r<m; r++) {
                for (int d=0; d<10; d++) {
                    int ps = subm(s, d%m);
                    int pr = subm(r, p10[i]*d%m);
                    addm(pr, ps*d%m);


                    int cd = str[n-i-1] - '0';
                    if (d > cd) {
                        add(dp[i][s][r][1], dp[i+1][ps][pr][1]);
                    } else if (d == cd) {
                        add(dp[i][s][r][0], dp[i+1][ps][pr][0]);
                        add(dp[i][s][r][1], dp[i+1][ps][pr][1]);
                    } else {
                        add(dp[i][s][r][1], dp[i+1][ps][pr][0]);
                        add(dp[i][s][r][1], dp[i+1][ps][pr][1]);
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i=0; i<m; i++) {
        add(ans, dp[0][i][0][0]);
        add(ans, dp[0][i][0][1]);
    }
    debug(ans);
    return ans;
}

bool check (string str) {
    int n = SZ(str);
    int ret = 0;
    for (int i=0; i<n; i++) {
        addm(ret, (str[i]-'0')*p10[i]%m);
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) {
            subm(ret, (str[i]-'0')*(str[j]-'0')%m);
        }
    }
    return ret == 0;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    int t;
    cin >> t;

    while (t--) {
        string L, R;
        cin >> L >> R;
        cin >> m;

        p10[0] = 1;
        for (int i=1; i<MAXN; i++) {
            p10[i] = p10[i-1] * 10 % m;
        }

        sub(L);

        int ans = (solve(R) + MOD - solve(L)) % MOD ;
        cout << ans << endl;

#ifdef tmd
        while (R != L) {
            ans -= check(R);
            sub(R);
        }
        assert(ans == 0);
#endif
    }
}

