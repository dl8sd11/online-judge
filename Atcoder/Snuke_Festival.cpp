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

const int MAXN = 100005;
const ll MOD = 1000000007;

int n;
vector<int> a, b, c;

void getVector (vector<int> &vec) {
    vec.resize(n);
    REP (i, n) {
        int d;
        cin >> d;
        vec[i] = d;
    }
    sort(vec.begin(), vec.end());
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n;

    getVector(a);
    getVector(b);
    getVector(c);

    ll ans = 0;
    for (auto v : b) {
        ll szu = lower_bound(a.begin(), a.end(), v) - a.begin();
        ll szd = c.end() - upper_bound(c.begin(), c.end(), v);

        ans += szu * szd;
    }

    cout << ans << endl;

}
