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

int n;
const int MAXN = 1000006;

bool mx[] = {1, 1, 0, 0, 0, 0, 0};
bool mn[] = {0, 0, 0, 0, 0, 1, 1};
int main () {
    IOS();
    cin >> n;

    int s1 = 0, s2 = 0;
    REP (i, n) {
        s1 += mn[i%7];
        s2 += mx[i%7];
    }

    cout << s1 << " " << s2 << endl;
}
