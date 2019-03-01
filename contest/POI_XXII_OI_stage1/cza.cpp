#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define SZ(i) ll(i.size())
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif
const ll INF = 0x3f3f3f3f3f3f3f3f;

vector<ll> permu;
ll ans,n,k,p;
set<ll> ban[6];
int main () {
    IOS();
    cin >> n >> k >> p;
    permu.emplace_back(n);
    REP1 (i,n-1) {
        permu.emplace_back(i);
    }
    REP (i,k) {
        ll a,b;
        cin >> a >> b;
        ban[a].insert(b);
    }
    do {
        bool flag = true;
        REP (i,n) {
            if (ban[permu[i]].find(permu[(i+1)%n])!=ban[permu[i]].end()) {
                flag = false;
                break;
            }
            if (abs(permu[i]-permu[(i+1)%n]) > p) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ans++;
        }
    }while(next_permutation(ALL(permu)));

    cout << ans << endl;
}