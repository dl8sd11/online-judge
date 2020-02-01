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

int n;
set<int> st;
vector<int> sd;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        int a;
        cin >> a;
        if (st.count(a)) {
            sd.emplace_back(a);
            st.erase(a);
        } else {
            st.insert(a);
        }
    }

    sort(sd.begin(), sd.end());

    if (SZ(sd) < 2) {
        cout << 0 << endl;
    } else {
        cout << ll(sd[SZ(sd)-1]) * sd[SZ(sd)-2] << endl;
    }
    return 0;
}
