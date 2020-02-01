#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i, n) for(int i=1; i<=n; i++)
#define pb push_back
#define eb emlace_back
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 1000006;

int n, k, id[MAXN];
int main () {
    IOS();

    cin >> n >> k;
    REP1 (i, n) {
        cin >> id[i];
    }

    REP1 (i, n) {
        if (k > i) {
            k -= i;
        } else {
            cout << id[k] << endl;
            return 0;
        }
    }
}
