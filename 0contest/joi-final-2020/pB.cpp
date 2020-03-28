#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define eb emplace_back
#define X first
#define Y second
#define MEM(i,a) memset(i,(a),sizeof(i))
#ifdef tmd
#define debug(...) fprintf(stderr,"%d(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){
    cerr<<x<<",";
    _do(y...);
}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define pary(...)
#define endl '\n'
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
vector<pll> art; // size, val
int main () {
    IOS();

    ll mx = 0, sum = 0;

    cin >> n;

    REP (i, n) {
        ll sz, va;
        cin >> sz >> va;
        art.eb(sz, va);
    }
    sort(ALL(art));


    ll ans = 0;
    for (int i=0; i<n; i++) {
        mx = max(art[i].X-sum, mx);
        sum += art[i].Y;
        ans = max(ans, mx+sum-art[i].X);
    }

    cout << ans << endl;
    return 0;
}
/*

15
1543361732 260774320
2089759661 257198921
1555665663 389548466
4133306295 296394520
*/
