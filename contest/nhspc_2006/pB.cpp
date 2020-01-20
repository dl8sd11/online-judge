#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define eb emplace_back
#define MEM(a,b) memset(a,(b),sizeof(a))
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
ll ans;
/*********Good***Luck*********/
int main () {
    IOS();
    cin >> n;
    vector<ll> pos = {0};
    REP (i, n) {
        ll d;
        cin >> d;
        pos.emplace_back(d);
    }
    sort(ALL(pos));

    REP1 (i, SZ(pos) - 1) {
        ans += (pos[i]-pos[i-1]) * (pos[i]-pos[i-1]);
    }

    cout << ans << endl;
    return 0;
}
