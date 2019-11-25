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

string str;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> str;

    ll ans = 0;

    int cnt = 0;
    for (int i=SZ(str)-1; i>=0; i--) {
        if (str[i] == 'A') {
            ans += cnt;
        } else if (i>0&&str[i]=='C'&&str[i-1]=='B') {
            cnt++;
            i--;
        } else {
            cnt = 0;
        }
    }

    cout << ans << endl;
}
