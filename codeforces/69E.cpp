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

int n, k, a[MAXN];
set<int> once;
map<int,int> occur;

/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> k;
    REP (i, n) {
        cin >> a[i];
        int cur = ++occur[a[i]];
        if (cur == 1) {
            once.insert(a[i]);
        } else if (cur == 2) {
            once.erase(a[i]);
        }

        if (i >= k-1) {
            if (once.empty()) {
                cout << "Nothing" << endl;
            } else {
                cout << *prev(once.end()) << endl;
            }
            cur = --occur[a[i-k+1]];
            if (cur == 0) {
                once.erase(a[i-k+1]);
            } else if (cur == 1) {
                once.insert(a[i-k+1]);
            }
        }
    }
}
