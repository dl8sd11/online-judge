#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef pair<int,int> pii;
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

const int INF = 0x3f3f3f3f;
const int MAXN = 2000003;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
tree<pii,null_type,greater<pii>,rb_tree_tag,tree_order_statistics_node_update> rk;

int n;
int f[MAXN];
int l[MAXN],pre[MAXN],suf[MAXN];
pii r[MAXN];

namespace SEG {
    ll dt[MAXN*2];
    void set(ll pos,ll val) {
        pos+=n;
        for (dt[pos]=max(dt[pos],val);pos>1;pos>>=1) {
            dt[pos>>1] = max(dt[pos],dt[pos^1]);
        }
    }
    ll query(ll l,ll r) {
        ll ret = 0;
        for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
            if (l&1) {
                ret = max(ret,dt[l++]);
            }
            if (r&1) {
                ret = max(ret,dt[--r]);
            }
        }
        return ret;
    }
};
int main () {
    cin >> n;
    REP1 (i,n) {
        char c;
        cin >> c;
        f[i] = (c == 'p' ? 1 : -1);
        pre[i] += pre[i-1] + f[i];
        rk.insert({pre[i],-i});
    }

    int cur = 0;
    REP1 (i,n) {
        int pos = int(rk.order_of_key({cur,-INF}));
        if (pos == SZ(rk)) {
            l[i] = n+1;
        } else {
            l[i] = (*rk.find_by_order(pos)).Y*-1;
        }
        cur += f[i];
        rk.erase({pre[i],-i});
    }
    assert(rk.empty());

    for (int i=n;i>=1;i--) {
        suf[i] += suf[i+1] + f[i];
        rk.insert({suf[i],i});
    }
    cur = 0;
    for (int i=n;i>=1;i--) {
        int pos = int(rk.order_of_key({cur,-INF}));
        if (pos == SZ(rk)) {
            r[i] = {0,i};
        } else {
            r[i] = {(*rk.find_by_order(pos)).Y,i};
        }
        cur += f[i];
        rk.erase({suf[i],i});
    }


    sort(r+1,r+n+1);
    ll ans = 0;
    ll idx = 0;
    REP1 (i,n) {
        while (idx <= n && r[idx].X < i) {
            SEG::set(r[idx].Y-1,r[idx].Y);
            idx++;
        }
        ll j = SEG::query(i-1,l[i]-1);
        ans = max(ans,j-i+1);
    }

    cout << ans << endl;
}