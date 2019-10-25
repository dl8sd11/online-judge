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

string str[] = {"Pen", "Pineapple", "Apple", "Pineapple pen"};
/*********************GoodLuck***********************/
int main () {
    IOS();

    int n;
    cin >> n;
    int idx = 3, rem = 0, rd = 0;
    REP1 (i, n) {
        if (rem == 0) {
            if (idx == 3) {
                rd++;
            }
            idx = (idx + 1) % 4;
            rem = rd;
        }
        rem--;

    }

    cout << str[idx] << endl;
}
