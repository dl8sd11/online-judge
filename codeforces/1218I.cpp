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

const int MAXN = 2003;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

int n;
bool s[MAXN][MAXN], t[MAXN][MAXN];
bool mg[MAXN];
set<int> st;

int djs[MAXN*4];
bool vis[MAXN*4];
vector<int> gp[MAXN*4];
int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    djs[x] = y;
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        REP (j, n) {
            char b;
            cin >> b;

            s[i][j] = b == '1';
        }
    }

    REP (i, n) {
        REP (j, n) {
            char b;
            cin >> b;

            t[i][j] = b == '1';
        }
    }

    REP (i, n) {
        char b;
        cin >> b;
        mg[i] = b == '1';
    }

    REP (i, n*4) {
        djs[i] = i;
    }

    bool no_solution = false;
    REP (i, n) {
        REP (j, n) {
            bool chg = s[i][j] ^ t[i][j];
            if (mg[i] && mg[j]) {
                if (chg) {
                    mrg(i*2, (j+n)*2+1);
                    mrg(i*2+1, (j+n)*2);
                } else {
                    mrg(i*2, (j+n)*2);
                    mrg(i*2+1, (j+n)*2+1);
                }
            } else if (mg[i] || mg[j]) {
                chg ^= 1;
                st.insert(!mg[i] ? i*2+chg : (j+n)*2+chg);
            } else {
                if (chg) {
                    no_solution = true;
                }
            }
        }
    }
    REP (i, n*4) {
        gp[fnd(i)].emplace_back(i);
    }
    debug(no_solution);

    set<int> fn;
    for (auto v : st) {
        if (!vis[fnd(v)]) {
            vis[fnd(v)] = true;
            for (auto el : gp[fnd(v)]) {
                fn.insert(el);
                debug(el);
            }
        }
    }

    REP (i, n) {
        if (fn.count(i*2) == 0 && fn.count(i*2+1) == 0) {
            assert(!vis[fnd(i*2)]);
            for (auto v : gp[fnd(i*2)]) {
                fn.insert(v);
            }
        }
    }
    REP (i, n) {
        if (fn.count((i+n)*2) == 0 && fn.count((i+n)*2+1) == 0) {
            assert(!vis[fnd((i+n)*2)]);
            for (auto v : gp[fnd((i+n)*2)]) {
                fn.insert(v);
            }
        }
    }

    REP (i, n) {
        no_solution |= (fn.count(i*2) && fn.count(i*2+1));
        no_solution |= (fn.count((i+n)*2) && fn.count((i+n)*2+1));
    }

    if (no_solution) {
        cout << -1 << endl;
    } else {
        vector<int> rw, cl;
        REP (i, n) {
            if (fn.count(i*2)) {
                rw.emplace_back(i);
            }
            if (fn.count((i+n)*2)) {
                cl.emplace_back(i);
            }
        }

        cout << SZ(rw) + SZ(cl) << endl;
        for (auto r : rw) {
            cout << "row " << r << endl;
        }
        for (auto c : cl) {
            cout << "col " << c << endl;
        }
    }
    return 0;
}
