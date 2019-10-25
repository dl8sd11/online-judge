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

ll k;
set<ll> ans;

void solve (ll a, ll b) {
    if ((a+b)&1LL) {
        return;
    }
    ll x = (a-b)/2;
    ll y= (a+b)/2;
    if (x != 0 && y != 0) {
        ans.insert(x*x);
        ans.insert(-y*y);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> k;
    for (ll i=1; i*i<=k; i++) {
        if (k%i == 0) {
            solve(i, k/i);
        }
    }

    for (ll i=1; i*i<=k; i++) {
        ll j = sqrt(k-i*i+0.5);
        if (i*i+j*j == k && j != 0) {
            ans.insert(-i*i);
        }
    }

    ans.erase(0);
    cout << SZ(ans) << endl;
    bool fs = true;
    for (auto v : ans) {
        if (!fs) {
            cout << " " << v;
        } else {
            cout << v;
            fs = false;
        }
    }
    if (SZ(ans)) {
        cout << endl;
    }
}
