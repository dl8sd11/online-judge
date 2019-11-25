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

const int MAXN = 200005;
const ll MOD = 1000000007;

string a, b;
int z[MAXN];

void build_zvalue () {
    int n = SZ(a);
    z[0] = 0;
    int bst = 0;

    REP1 (i, n-1) {
        if (bst+z[bst] >= i) {
            z[i] = min(bst+z[bst]-i, z[i-bst]);
        }
        while (i+z[i]<n&&a[i+z[i]]==a[z[i]]) {
            z[i]++;
        }
        if (i+z[i]>bst+z[bst]) {
            bst = i;
        }
    }
}

int match () {
    int sza = SZ(a);
    a = a + '@';
    a = a + b;

    build_zvalue();
    int cnt = 0;
    for (int i=sza+1; i<SZ(a); i++) {
        cnt += z[i] == sza;
    }
    return cnt;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> a >> b;

    cout << match() << endl;
}
