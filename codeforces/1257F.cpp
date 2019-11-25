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

const int MAXN = 100005;
const ll MOD = 1000000007;
const int hf = 15;
const int fll = (1<<15) - 1;

int n, a[MAXN];
map<vector<int>, int> L;

void normalize(vector<int> &vec) {
    int mn = *min_element(vec.begin(), vec.end());
    for (auto &v : vec) {
        v -= mn;
    }
}

void complement(vector<int> &vec) {
    int mx = *max_element(vec.begin(), vec.end());
    for (auto &v : vec) {
        v = mx - v;
    }
}

void build_left() {
    REP (mask, (1<<hf)) {
        vector<int> cur;
        REP (i, n) {
            int nw = (a[i] & (fll<<hf)) ^ (mask<<hf);
            cur.emplace_back(__builtin_popcount(nw));
        }

        normalize(cur);
        if (L.count(cur) == 0) {
            L[cur] = mask << hf;
        }
    }
}

int query_right() {
    REP (mask, (1<<hf)) {
        vector<int> cur;
        REP (i, n) {
            int nw = (a[i] & fll) ^ mask;
            cur.emplace_back(__builtin_popcount(nw));
        }

        complement(cur);
        if (L.count(cur)) {
            return L[cur] + mask;
        }
    }
    return -1;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n;
    REP (i, n) {
        cin >> a[i];
    }

    build_left();
    int ans = query_right();

    cout << ans << endl;
}

