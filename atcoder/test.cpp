#include <iostream>
#include <cstring>
#include <vector>
#define mod 1000000007
using namespace std;
typedef long long ll;
const int MAXN = 305;
vector<pair<int , int> >vc[MAXN];
int dp[MAXN][MAXN][MAXN];
bool check(int r , int g , int b) {
    int k = max(r , max(g , b));
    int len = vc[k].size();
    for(int i = 0 ; i < len ; i++) {
        int l = vc[k][i].first , x = vc[k][i].second;
        int cnt = 0;
        if(r >= l) cnt++;
        if(g >= l) cnt++;
        if(b >= l) cnt++;
        if(cnt != x) return false;
    }
    return true;
}
int main() {
    int n , m;
    cin >> n >> m;
    for(int i = 0 ; i < m ; i++) {
        int l , r , x;
        cin >> l >> r >> x;
        vc[r].push_back(make_pair(l , x));
    }
    memset(dp , 0 , sizeof(dp));
    dp[0][0][0] = 1;
    ll ans = 0;
    for(int r = 0 ; r <= n ; r++) {
        for(int g = 0 ; g <= n ; g++) {
            for(int b = 0 ; b <= n ; b++) {
                if(!dp[r][g][b]) continue;
                if(!check(r , g , b)) {
                    dp[r][g][b] = 0;
                    continue;
                }
                int k = max(r , max(g , b));
                if(k == n) ans = (ans + (ll)dp[r][g][b]) % mod;
                dp[k + 1][g][b] += dp[r][g][b] % mod;
                dp[k + 1][g][b] %= mod;
                dp[r][k + 1][b] += dp[r][g][b] % mod;
                dp[r][k + 1][b] %= mod;
                dp[r][g][k + 1] += dp[r][g][b] % mod;
                dp[r][g][k + 1] %= mod;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
