#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define SZ(i) ll(i.size())
#define MEM(i,n) memset(i,(n),sizeof(i))
#define X first
#define Y second
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template <typename T> void _do(T &&x){cerr<<x<<endl;}
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#endif

const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 1000003;
ll n,bit[MAXN];
char s[MAXN],t[MAXN];
vector<ll> p[30];

void add(ll pos,ll val) {
    for (pos++;pos<=n;pos+=-pos&pos) {
        bit[pos] += val;
    }
}
ll query(ll pos) {
    ll ret = 0;
    for (pos++;pos>=1;pos-=-pos&pos) {
        ret += bit[pos];
    }
    return ret;
}
int main () {
    IOS();
    cin >> n;
    cin >> s;
    cin >> t;
    for (ll i=n-1;i>=0;i--) {
        p[t[i]-'A'].emplace_back(i);
    }
    REP (i,n) {
        add(i,1);
    }
    ll ans = 0;
    REP (i,n) {
        ll cur = p[s[i]-'A'].back();
        p[s[i]-'A'].pop_back();

        add(cur,-1);
        ans += query(cur);
    }

    cout << ans << endl;
}