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

const int MAXN = 200005;
const ll MOD = 1000000007;

int n, deg[MAXN], mex[MAXN];
vector<int> edg[MAXN];
vector<int> rev[MAXN];

set<int> st;
void calc (int nd) {
    mex[nd] = -1;
    st.clear();

    for (auto v : edg[nd]) {
        if (mex[v] != -1) {
            st.insert(mex[v]);
        }
    }
    int lst = -1;
    for (auto v : st) {
        if (v != lst + 1) {
            mex[nd] = lst + 1;
            break;
        }
        lst = v;
    }
    if (mex[nd] == -1) {
        mex[nd] = lst + 1;
    }

    assert(mex[nd] >= 0);
}

bool check (int nd) {
    int cur = -1;
    st.clear();

    for (auto v : edg[nd]) {
        if (mex[v] != -1) {
            st.insert(mex[v]);
        }
    }
    int lst = -1;
    for (auto v : st) {
        if (v != lst + 1) {
            cur = lst + 1;
            break;
        }
        lst = v;
    }
    if (cur == -1) {
        cur = lst + 1;
    }


    return cur == mex[nd];
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    memset(mex, -1, sizeof(mex));

    cin >> n;
    REP1 (i, n) {
        int p;
        cin >> p;
        edg[p].emplace_back(i);
        rev[i].emplace_back(p);
        deg[p]++;
        deg[i]++;
    }

    vector<int> que;
    int ft = 0;
    REP1 (i, n) {
        if (deg[i] == 1) {
            que.emplace_back(i);
        }
    }
    while (ft != SZ(que)) {
        int cur = que[ft];
        ft++;

        calc(cur);
        for (auto v : edg[cur]) {
            if ((deg[v]--) == 2) {
                que.emplace_back(v);
            }
        }
        for (auto v : rev[cur]) {
            if ((deg[v]--) == 2) {
                que.emplace_back(v);
            }
        }
    }

    vector<int> cyc;
    int rt = -1;
    REP1 (i, n) {
        if (deg[i] == 2) {
            rt = i;
        }
    }

    int idx = rt;
    while (true) {
        cyc.emplace_back(idx);
        int nxt = idx;
        for (auto v : edg[idx]) {
            if (deg[v] == 2) {
                nxt = v;
                break;
            }
        }
        idx = nxt;
        if (idx == rt) {
            break;
        }
    }

    reverse(cyc.begin(), cyc.end());
    debug(SZ(cyc));
    #ifdef tmd
    for (auto c : cyc) {
        cout << c << " ";
    }
    cout << endl;
    #endif

    calc(cyc[0]);
    for (int i=1; i<SZ(cyc); i++) {
        calc(cyc[i]);
    }


    #ifdef tmdd
    REP1 (c, n) {
        cout << mex[c] << " ";
    }
    cout << endl;
    #endif
    if (check(cyc[0])) {
        cout << "POSSIBLE" << endl;
        return 0;
    }

    calc(cyc[0]);
    for (int i=1; i<SZ(cyc); i++) {
        calc(cyc[i]);
    }
    #ifdef tmdd
    REP1 (c, n) {
        cout << mex[c] << " ";
    }
    cout << endl;
    #endif
    if (check(cyc[0])) {
        cout << "POSSIBLE" << endl;
        return 0;
    }

    cout << "IMPOSSIBLE" << endl;
    return 0;
}
