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

const int MAXN = 1003;
const ll MOD = 1000000007;

int n, p[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n;
    REP (i, n) {
        cin >> p[i];
    }

    int mid = max_element(p,p+n)-p+1;
    p[mid-1] = -1;
    int m2 = *max_element(p,p+n);

    cout << mid << " " << m2 << endl;
}
