#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3","unroll-loops")
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
int t, n, a[MAXN];

gp_hash_table<int,int> cnt;
gp_hash_table<int,int> rem;

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n;

        cnt.clear(), rem.clear();
        REP (i, n) {
            cin >> a[i];
            cnt[a[i]]++;
        }

        ll ans = numeric_limits<ll>::max(), org = 0;
        for (auto p : cnt) {
            if (p.second % p.first != 0) {
                rem[p.first] = p.second % p.first;
            }
            org += ((p.second + p.first - 1) / p.first) * p.first;
        }

        REP (i, n) {
            if (rem.find(a[i]) != rem.end()) {
                int x = rem[a[i]];
                ll tmp = org;
                if (x == 1) {
                    tmp -= a[i];
                    if (rem.size() == 1) {
                        tmp++;
                    }
                } else {
                    if (rem.size() == 1) {
                        tmp++;
                    }
                }
                ans = min(ans, tmp);
            } else {
                if (a[i] == 1) {
                    if (rem.size()) {
                        ans = min(ans, org - 1);
                    } else {
                        ans = min(ans, org + 1);
                    }
                } else if (rem.size()) {
                    ans = min(ans, org);
                } else {
                    ans = min(ans, org+1);
                }
            }
        }

        cout << ans << endl;
    }

}
