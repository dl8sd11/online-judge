#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 1000006;
const ll MOD = 1000000007;

ll t, n;

ll rem (ll val) {
    while (val >= 3) {
        val = val % 3 + val/3;
    }
    return val;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    debug(rem(8));

    cin >> t;
    while (t--) {
        cin >> n;

        list<pair<char, ll> > lst;

        REP (i, n) {
            char c;
            ll d;
            cin >> c >> d;
            lst.insert(lst.end(), {c,d});
        }

        auto it = lst.begin();
        while (it != lst.end()) {
            auto nxt = next(it);
            debug(it->first, it->second);
            if (it!=lst.begin()) {
                auto prv = prev(it);
                if (it->first == prv->first) {
                    it->second += prv->second;
                    lst.erase(prv);
                }
            }
            if (it == prev(lst.end())) {
                it->second = rem(it->second);
            } else {
                if (it->second >= 3) {
                    int add = it->second / 3;
                    if (prev(lst.end())->first ==  it->first) {
                        prev(lst.end())->second = prev(lst.end())->second + add;
                    } else {
                        lst.insert(lst.end(), {it->first, add});
                    }
                    if (it->second % 3 == 0) {
                        lst.erase(it);
                    } else {
                        it->second %= 3;
                    }
                }
            }
            it = nxt;

            #ifdef tmd
            for (auto x : lst) {
                cout << x.first << " " << x.second << ", ";
            }
            cout << endl;
            #endif
        }
        for (auto ptr=next(lst.begin()); ptr!=lst.end(); ptr++) {
            assert(ptr->first != prev(ptr)->first);
        }

        ll ans = 0;
        for (auto ptr : lst) {
            ans += ptr.second;
        }
        cout << ans << endl;

    }
    return 0;
}
