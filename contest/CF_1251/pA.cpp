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

const int MAXN = 500005;
const ll MOD = 1000000007;

int t;
string str;
bool ans[27];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;

    while (t--) {
        int cur = 1;
        memset(ans, 0, sizeof(ans));
        cin >> str;
        for (int i=1; i<=SZ(str); i++) {
            if (i == SZ(str) || str[i] != str[i-1]) {
                if (cur == 1) {
                    ans[str[i-1]-'a'] = true;
                }
                cur = 0;
            }
            cur^=1;
        }

        for (int i=0; i<26; i++) {
            if (ans[i] ) {
                cout << char(i + 'a');
            }
        }
        cout << endl;
    }
}
