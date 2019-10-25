#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 1000006;
const ll MOD = 1000000007;

int n;
string str1, str2;
vector<bool> dom;
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> str1 >> str2;
    REP (i, n) {
        if (str1[i] == str2[i]) {
            dom.emplace_back(1);
        } else {
            dom.emplace_back(0);
            i++;
        }
    }

    ll cur = dom[0] ? 3 : 6;
    for (int i=1; i<SZ(dom); i++) {
        if (dom[i]) {
            if (dom[i-1]) {
                cur = cur * 2 % MOD;
            }
        } else {
            if (!dom[i-1]) {
                cur = cur * 3 % MOD;
            } else {
                cur = cur * 2 % MOD;
            }
        }
    }

    cout << cur << endl;
    return 0;
}
