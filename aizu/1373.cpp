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


typedef pair<int, int> pii;

int n, x;
set<pii> st;

void build (int l, int r) {
    if (l <= r) {
        auto ptr = st.lower_bound(pii(l, -1));
        if (ptr != st.begin()) {
            auto ptrl = prev(ptr);
            if (ptrl->second == l - 1) {
                l = ptrl->first;
            }
        }
        if (ptr != st.end() && ptr->first == r + 1) {
            st.erase(ptr);
            r = ptr->second;
        }
        st.insert(pii(l, r));
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    st.insert(pii(0, MOD));
    REP (i, n) {
        cin >> x;
        if (st.begin()->first != 0) {
            cout << "No" << endl;
            continue;
        }
        auto ptr = st.lower_bound(pii(x+1, -1));
        if (ptr == st.begin()) {
            cout << "No" << endl;
        } else {
            ptr = prev(ptr);
            if (ptr->second >= x) {
                cout << "Yes" << endl;
                pii cur = *ptr;
                st.erase(ptr);
                build(cur.first, x-1);
                build(x+1, cur.second);
            } else {
                if (ptr->second == 0 && (*next(ptr)) != pii(x+1, MOD)) {
                    cout << "No" << endl;
                    continue;
                }
                cout << "Yes" << endl;
                pii cur = *ptr;
                st.erase(ptr);
                build(cur.first, cur.second - 1);
                build(cur.second + 1, x);
            }
        }
    }
    return 0;
}
