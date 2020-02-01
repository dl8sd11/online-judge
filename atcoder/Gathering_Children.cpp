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

const int MAXN = 1000006;
const ll MOD = 1000000007;

string str;
bool b[MAXN];
int l[MAXN], r[MAXN], ans[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> str;
    int n = SZ(str);

    int lst[2] = {-1, -1};
    REP (i, n) {
        b[i] = str[i] == 'R';
        l[i] = lst[b[i]^1];
        lst[b[i]] = i;
    }

    lst[0] = lst[1] = n;
    for (int i=n-1; i>=0; i--) {
        r[i] = lst[b[i]^1];
        lst[b[i]] = i;

        if (b[i]) {
            ans[(r[i]-i)&1 ? r[i]-1 : r[i]]++;
        } else {
            ans[(i-l[i])&1 ? l[i]+1 : l[i]]++;
        }
    }

    REP (i, n) {
        cout << ans[i] << " \n"[i==n-1];
    }

    return 0;
}
