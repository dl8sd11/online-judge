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
template<typename T> ostream &operator << (ostream &os,set<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 200005;
const ll MOD = 1000000007;

string cmd;
vector<int> cur;
ll dp[MAXN];
set<int> lf;
vector<int> mt;

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> cmd;

    int n = SZ(cmd);
    ll ans = 0;
    REP (i, n) {
        int csz = SZ(cur);
        dp[csz] = 0;
        if (cmd[i] == '(') {
            cur.eb(i);
            lf.insert(csz);
        } else if (cmd[i] == ')') {
            cur.eb(i);

            if (SZ(lf) >= 1) {
                auto ed = prev(lf.end());

                dp[csz] = (*ed > 0 ? dp[(*ed)-1] : 0) + 1;
                mt.eb(*ed);
                lf.erase(ed);
                ans += dp[csz];
            } else {
                mt.eb(-1);
            }

        } else {
            if (cmd[cur.back()] == ')') {
                if (mt.back() != -1) {
                    lf.insert(mt.back());
                    ans -= dp[csz-1];
                }
                dp[csz-1] = 0;
                mt.pop_back();
            } else {
                lf.erase(csz-1);
            }
            cur.pop_back();
        }

        cout << ans << endl;
    }
}
