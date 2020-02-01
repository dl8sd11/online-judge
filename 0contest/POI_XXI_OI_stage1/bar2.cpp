#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef pair<int,int> pii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
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
const int MAXN = 100003;

int n;
int f[MAXN];
int l[MAXN],r[MAXN];
char c;
int main () {
    scanf(" %d",&n);
    assert(n <= 10003);
    getchar();
    bool flag = false;
    REP1 (i,n) {
        c = getchar();
        flag |= c == 'p';
        f[i] = (c=='p'?1:-1);
    }
    if (!flag) {
        cout << 0 << endl;
        return 0;
    }

    REP1 (i,n) {
        int sum = 0;
        for (ll j=i;j<=n+1;j++) {
            sum += f[j];
            if (sum < 0 || j == n+1) {
                l[i] = j;
                break;
            }
        }
        sum = 0;
        for (ll j=i;j>=0;j--) {
            sum += f[j];
            if (j == 0 || sum < 0) {
                r[i] = j;
                break;
            }
        }
    }

    #ifdef tmd
        REP1 (i,n) {
            cout << l[i] << " \n"[i==n];
        }
        REP1 (i,n) {
            cout << r[i] << " \n"[i==n];
        }

    #endif

    int ans = 0;
    REP1 (i,n) {
        int mx = i-1;
        if (f[i] > 0) {
            for (int j=l[i]-1;j>=i;j--) {
                if (r[j] < i) {
                    mx = j;
                    break;
                }
            }
        }
        ans = max(ans,mx-i+1);
    }
    cout << ans << endl;
}