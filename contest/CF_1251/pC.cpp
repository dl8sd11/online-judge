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

const int MAXN = 500005;
const ll MOD = 1000000007;

int t;
vector<char> o, e;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        string str;
        cin >> str;
        o.clear();
        e.clear();
        for (auto v : str) {
            if ((v-'a') & 1) {
                o.emplace_back(v);
            } else {
                e.emplace_back(v);
            }
        }

        reverse(o.begin(), o.end());
        reverse(e.begin(), e.end());
        REP (i, SZ(str)) {
            if (o.empty()) {
                cout << e.back();
                e.pop_back();
            } else if (e.empty() || o.back() < e.back()) {
                cout << o.back();
                o.pop_back();
            } else {
                cout << e.back();
                e.pop_back();
            }
        }
        cout << endl;
    }

}
