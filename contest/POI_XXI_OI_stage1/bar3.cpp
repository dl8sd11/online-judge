#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define X first
#define Y second
#define SZ(i) ll(i.size())
#define MEM(i,n) memset(i,(n),sizeof(i))
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#define endl '\n'
#endif

const int INF = 0x3f3f3f3f;
const int MAXN = 2000003;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
tree<pii,null_type,greater<pii>,rb_tree_tag,tree_order_statistics_node_update> rk;

int n;
int f[MAXN],ans;
int main () {
    cin >> n;
    REP (i,n) {
        char c;
        cin >> c;
        f[i] = (c=='p'?1:-1);
    }

    REP (i,n) {
        REP (j,i+1) {
            int sum = 0;
            bool flag = false;
            for (int k=j;k<=i;k++) {
                sum += f[k];
                if (sum < 0) {
                    flag = true;
                }
            }

            sum = 0;
            for (int k=i;k>=j;k--) {
                sum += f[k];
                if (sum < 0) {
                    flag = true;
                }
            }
            if (!flag) {
                debug(i);
                debug(j);
                ans = max(ans,i-j+1);
            }
        }
    }

    cout << ans << endl;
}