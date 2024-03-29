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
const int MAXC = 5003;
ll w, m;

vector<ll> num;

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> w >> m;
    while (m > 0) {
        num.emplace_back(m % w);
        m /= w;
    }
    num.emplace_back(0);

    for (ll i=0; i<SZ(num); i++) {
        if (num[i] <= 1) {
            continue;
        } else {
            num[i + 1]++;
            num[i] -= w;
            if (abs(num[i]) > 1) {
                cout << "NO" << endl;
                return 0;
            }
        }
    }

    cout << "YES" << endl;

}
