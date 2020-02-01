#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i, n) for(int i=1; i<=n; i++)
#define pb push_back
#define eb emlace_back
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 500006;

int n, m, p;
int mat[MAXN];
set<int> rem;
vector<int> stk;

int del (int l, int r) {
    if (l > r) {
        swap(l, r);
    }

    auto ptr = rem.lower_bound(l);
    while (ptr!=rem.end() && *ptr <= r) {
        rem.erase(ptr);
        ptr = rem.lower_bound(l);
    }

    if (rem.empty()) {
        return -1;
    }
    ptr = rem.lower_bound(r);
    if (ptr == rem.end()) {
        ptr--;
    }
    return *ptr;
}
int main () {
    IOS();

    cin >> n >> m >> p;

    string b;
    cin >> b;
    REP (i, n) {
        if (b[i] == ')') {
            mat[i] = stk.back();
            mat[stk.back()] = i;
            stk.pop_back();
        } else {
            stk.emplace_back(i);
        }
        rem.insert(i);
    }

#ifdef tmd
    REP (i, n) {
        cout << mat[i];
    }
    cout << endl;
#endif

    p--;
    while (m--) {
        debug(p);
        char cmd;
        cin >> cmd;
        if (cmd == 'R') {
            p = *(rem.lower_bound(p+1));
        } else if (cmd == 'L') {
            p = *prev(rem.lower_bound(p));
        } else {
            p = del(p, mat[p]);
        }

#ifdef tmd
        for (auto v : rem) {
        cout << v << " ";
        }
        cout << endl;

#endif
    }

    for (auto v : rem) {
        cout << b[v];
    }
    cout << endl;
}
