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

string str;
int n;

int findEdge (int st, int dl) {
    int ptr = st;
    while (ptr >= 0 && ptr < n && str[ptr] == str[st]) {
        ptr += dl;
    }
    return ptr;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> str;
    n = SZ(str);

    int l = findEdge((n-1)/2, -1);
    int r = findEdge(n/2, 1);
    if (str[(n-1)/2] != str[n/2]) {
        cout << n/2 << endl;
    } else {
        cout << min(r, n-l-1) << endl;
    }

}
