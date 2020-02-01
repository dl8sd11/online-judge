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

vector<string> sa;
/*********************GoodLuck***********************/
int main () {
    IOS();

    ll ans = 0;
    int n;
    cin >> n;
    REP (i, n) {
        string s;
        cin >> s;
        sort(s.begin(), s.end());
        sa.emplace_back(s);
    }

    sort(sa.begin(), sa.end());

    int cnt = 1;
    REP1 (i, SZ(sa)) {
        if (i == SZ(sa) || sa[i] != sa[i-1]) {
            debug(cnt);
            ans += cnt * ll(cnt - 1) / 2;
            cnt = 0;
        }
        cnt++;
    }

    cout << ans << endl;


    return 0;
}
