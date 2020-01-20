#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define MEM(a,b) memset(a,(b),sizeof(a))
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define eb emplace_back
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d (%s) = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#define endl '\n'
#endif

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;
int t, n;
void upd(pair<int,int> &p, int val) {
    p.first = min(p.first, val);
    p.second = max(p.second, val);
}

int main () {
    IOS();
    cin >> t;
    while (t--) {
        cin >> n;
        pair<int,int> x = {MOD, -MOD}, y = {MOD, -MOD};

        REP (i, n) {
            int xx, yy;
            cin >> xx >> yy;
            upd(x, xx);
            upd(y, yy);
        }

        cout << (x.second - x.first) * (y.second - y.first) << endl;
    }
}

/*
2
10
10 1
10 2
8 2
8 5
7 5
7 2
5 2
5 4
2 4
2 1
4
2 1
5 1
5 4
2 4
*/
