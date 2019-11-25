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

double a, b, x;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> a >> b >> x;
    double c;
    if (x/a <= a*b/2) {
        c = x/a*2/b;
        debug(atan(c/b));
        cout << fixed << setprecision(10) << 90-atan(c/b)/acos(-1)*180 << endl;
    } else {
        c = 2*(b-x/a/a);
        cout << fixed << setprecision(10) << 90-atan(a/c)/acos(-1)*180 << endl;
    }
    debug(a, b, c);

}
