#include <bits/stdc++.h>
using namespace std;
typedef int ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define X first
#define Y second
#define SZ(i) ll(i.size())
#define MEM(i,n) memset(i,(n),sizeof(i))
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#define endl '\n'
#endif

const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 500003;
const ll D = 20;

ll bit[MAXN][D];
ll n,m;
ll p[MAXN];
vector<ll> app[MAXN];
void add(ll pos,ll idx) {
    for (;pos<=n;pos+=-pos&pos) {
        bit[pos][idx]++;
    }
}

ll query(ll pos,ll idx) {
    ll ret = 0;
    for (;pos>=1;pos-=-pos&pos) {
        ret += bit[pos][idx];
    }
    return ret;
}
int main () {
    cin >> n >> m;
    REP1 (i,n) {
        cin >> p[i];
        app[p[i]].emplace_back(i);
        REP (j,D) {
            if ((1<<j)&p[i]) {
                add(i,j);
            }
        }
    }
    REP (i,m) {
        ll l,r;
        cin >> l >> r;
        ll q = 0;
        REP (j,D) {
            if (query(r,j)-query(l-1,j) > (r-l+1)/2) {
                q += (1<<j);
            }
        }
        ll cnt = 0;
        if (q >= 1 && q <= n) {
            cnt = upper_bound(ALL(app[q]),r)-lower_bound(ALL(app[q]),l);
        }
        if (cnt > (r-l+1)/2) {
            cout << q << endl;
        } else {
            cout << 0 << endl;
        }
    }
}