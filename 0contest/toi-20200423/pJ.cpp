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

const int MAXN = 1003;
const int MOD = 1000000007;

string str;
int dp[MAXN], pre[MAXN], suf[MAXN];

void add (int &x, int y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    while (cin >> str) {

        int sz = 1;

        memset(dp, 0, sizeof(dp));
        memset(pre, 0, sizeof(pre));
        memset(suf, 0, sizeof(suf));
        dp[1] = 1;
        pre[1] = 1;
        suf[1] = 1;
            pary(dp, dp+sz+1);
        for (auto c : str) {
            sz++;
            if (c == 'D') {

                dp[sz] = 0;
                for (int j=sz-1; j>=1; j--) {
                    dp[j] = suf[j];
                }
            } else if (c == 'I') {
                for (int j=1; j<=sz; j++) {
                    dp[j] = pre[j-1];
                }
            } else {
                for (int i=1; i<=sz; i++) {
                    dp[i] = suf[1];
                }
            }

            for (int i=1; i<=sz; i++) {
                pre[i] = dp[i];
                add(pre[i], pre[i-1]);
            }
            for (int i=sz; i>=1; i--) {
                suf[i] = dp[i];
                add(suf[i], suf[i+1]);
            }
            pary(dp, dp+sz+1);
        }

        cout << pre[sz] << endl;

    }


}

