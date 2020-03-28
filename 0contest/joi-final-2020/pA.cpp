#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define eb emplace_back
#define X first
#define Y second
#define MEM(i,a) memset(i,(a),sizeof(i))
#ifdef tmd
#define debug(...) fprintf(stderr,"%d(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){
    cerr<<x<<",";
    _do(y...);
}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define pary(...)
#define endl '\n'
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 100005;

int n, k;
int t[MAXN];
vector<int> dl;

int main () {
    IOS();

    cin >> n >> k;
    REP (i, n) {
        cin >> t[i];
        if (i) {
            dl.eb(t[i]-t[i-1]-1);
        }
    }
    sort(ALL(dl));

    int sum = t[n-1] - t[0] + 1;
    REP (i, min(k-1, SZ(dl))) {
        sum -= dl[SZ(dl)-i-1];
    }

    cout << sum << endl;

    return 0;
}
