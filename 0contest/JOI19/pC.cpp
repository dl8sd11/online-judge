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

const int MAXN = 402;
const int MOD = 0x3f3f3f3f;

int n;
int dp[2][MAXN][MAXN][3];
int g[MAXN];
string str;

int cnt[3];
int pre[MAXN][3];
vector<int> app[3];

int shf (int x, int y) {
    return x + y >= 3 ? x + y - 3 : x + y;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    cin >> str;

    REP (i, 3) {
        app[i].eb(-1);
    }

    REP (i, SZ(str)) {
        if (str[i] == 'R') {
            g[i] = 0;
        } else if (str[i] == 'G') {
            g[i] = 1;
        } else {
            g[i] = 2;
        }
        app[g[i]].eb(i);
        cnt[g[i]]++;
        for (int j=0; j<3; j++) {
            pre[i][j] = cnt[j];
        }
    }
    #define cdp dp[i&1]
    #define pdp dp[(i&1)^1]

    memset(dp, 0x3f, sizeof(dp));

    int ans = MOD;

    dp[0][0][0][0] = 0;
    dp[0][0][0][1] = 0;
    dp[0][0][0][2] = 0;

    for (int i=1; i<=n; i++) {
        for (int lst=0; lst<3; lst++) {
            for (int r=0; r<=i; r++) {
                for (int g=0; g<=i; g++) {
                    cdp[r][g][lst] = MOD;

                    int y = i - r - g;
                    if (y < 0) {
                        break;
                    }

                    if (r > cnt[0] || g > cnt[1] || y > cnt[2]) {
                        continue;
                    }

                    int rr = r - (lst == 0);
                    int gg = g - (lst == 1);
                    int yy = y - (lst == 2);

                    if (min({rr,gg,yy}) < 0) {
                        continue;
                    }

                    int prv = min(pdp[rr][gg][shf(lst,1)], pdp[rr][gg][shf(lst,2)]);
//                    debug(pdp[rr][gg][shf(lst,1)], pdp[rr][gg][shf(lst,2)]);
                    int trans = 0;

                    int cur[3];
                    cur[0] = r;
                    cur[1] = g;
                    cur[2] = y;

                    int pos = app[lst][cur[lst]];
                    trans = 0;
                    for (int x=0; x<3; x++) {
                        if (x != lst) {
                            if (app[x][cur[x]] < pos) {
                                trans += pre[pos][x] - cur[x];
                            }
                        }
                    }

//                    debug(i, r, g, y, lst,trans, prv);


                    if (prv != MOD) {
                        cdp[r][g][lst] = prv + trans;
                        debug(i,r,g,y,lst,prv,trans);
                        if (i == n) {
                            assert(r == cnt[0] && g == cnt[1] && y == cnt[2]);
                            ans = min(ans, cdp[r][g][lst]);
                        }
                    }
                }
            }
        }
    }

    cout << (ans == MOD ? -1 : ans) << endl;


}
