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

int t, n;
vector<pair<ll,int> > qry;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n;
        qry.clear();
        REP (i, n) {
            ll l, r;
            cin >> l >> r;
            qry.emplace_back(l,1);
            qry.emplace_back(r+1,-1);
        }
        sort(qry.begin(), qry.end());

        int ans = 0, cur = 0;
        for (int i=0; i<SZ(qry);) {
            ll x = qry[i].first;
            while (i < SZ(qry) && qry[i].first == x) {
                cur += qry[i].second;
                i++;
            }
            ans = max(ans, cur);
        }

        cout << ans << endl;
    }

    return 0;
}
