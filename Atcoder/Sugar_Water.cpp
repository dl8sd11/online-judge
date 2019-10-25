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

int a, b, c, d, e, f;

bool bt (pair<int,int> org, pair<int,int> nw) {
    if (org.second == 0) {
        return true;
    }
    return org.first * (nw.second + nw.first) <= (org.second + org.first) * nw.first;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> a >> b >> c >> d >> e >> f;

    pair<int,int> ans;
    for (int i=0; i*100*a<=f; i++) {
        for (int j=0; j*100*b+i*100*a<=f; j++) {
            int rem = f - (i*100*a+j*100*b);
            rem = min(rem, (i*a+j*b) * e);
            int lf = rem % (c*d);
            int mx = 0;
            for (int x=0;x*c<=lf; x++) {
                for(int y=0; x*c+y*d<=lf; y++) {
                    mx = max(x*c+y*d, mx);
                }
            }

            pair<int,int> nw = {mx+rem/(c*d)*(c*d), 100*(i*a+j*b)};
            debug(i, j, f, rem, nw.first, nw.second);
            if (bt(ans, nw)) {
                ans = nw;
            }
        }
    }

    cout << ans.second+ans.first << " " << ans.first << endl;
}
