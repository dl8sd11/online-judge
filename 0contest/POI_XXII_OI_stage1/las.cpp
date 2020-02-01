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
ll n;
ll c[30];

ll dic[30];
ll cnt[30];
bool check() {
    REP (i,n) {
        ll cur = c[dic[i]] / cnt[dic[i]];
        ll nid = (dic[i] == i ? (i+1)%n : i);
        ll chg = c[nid] / (cnt[nid]+1);
        if (chg > cur) {
            return false;
        }
    }
    return true;
}
void dfs(ll idx) {
    debug(idx);
    if (idx == n) {
        if (check()) {
            REP (i,n) {
                cout << dic[i]+1 << " \n"[i==n-1];
            }
            exit(0);
        }
        return;
    }

    dic[idx] = idx;
    cnt[idx]++;
    dfs(idx+1);
    cnt[idx]--;

    dic[idx] = (idx+1)%n;
    cnt[(idx+1)%n]++;
    dfs(idx+1);
    cnt[(idx+1)%n]--;
}
int main () {
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> c[i];
        c[i] *= 2;
    }

    dfs(0);
    cout << "NIE" << endl;
}