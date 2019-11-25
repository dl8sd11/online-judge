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

long long inv(long long a, long long b){
 return 1<a ? b -inv(b%a,a)*b/a : 1;
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    ll a, n;
    cin >> a >> n;
    if (a == 0) {
        cout << "No Inverse" << endl;
    } else if (a)
    ll iv = inv(a, n);
    assert(iv * a % n == 1);
    cout << iv << endl;
}
