#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define eb emplace_back


const int MAXN = 100005;
const ll MOD = 1000000007;

int n, m, p[MAXN], t[MAXN];
vector<int> edge[MAXN];

int sz[MAXN], in[MAXN], ch[MAXN], pa[MAXN], dep[MAXN], tp[MAXN];
bool state[MAXN];

void dfs_sz (int nd) {
    sz[nd] = 1;
    for (auto v : edge[nd]) {
        dfs_sz(v);
        sz[nd] += sz[v];
        if (sz[v] > sz[ch[nd]]) {
            ch[nd] = v;
        }
    }
}

int tme;
void dfs_ord (int nd, int pp) {
    in[nd] = tme++;
    pa[in[nd]] = in[p[nd]];
    dep[in[nd]] = dep[in[p[nd]]] + 1;
    tp[nd] = pp;

    if (ch[nd] != 0) {
        dfs_ord(ch[nd], pp);
    }
    for (auto v : edge[nd]) {
        if (v != ch[nd]) {
            dfs_ord(v, v);
        }
    }
}

int cnt[MAXN], ans;
bool des[MAXN];

template<int dl>
void chain (int l, int r) {
    if (dl > 0) {
        for (int i=l; i<=r; i++) {
            ans += cnt[i] == 0;
            cnt[i]++;
        }
    } else {
        for (int i=l; i<=r; i++) {
            cnt[i]--;
            ans -= cnt[i] == 0;
        }
    }
}

void upd (int nd, int dl) {
    int lf = nd;
    while (nd != 0) {
        if (dl > 0) {
            chain<1>(in[tp[nd]], in[nd]);
        } else {
            chain<-1>(in[tp[nd]], in[nd]);
        }
        nd = p[tp[nd]];
    }

    lf = in[lf];
    if (dl > 0) {
        if (cnt[lf] > 0) {
            ans--;
        }
        cnt[lf] += MOD;
    } else {
        cnt[lf] -= MOD;
        if (cnt[lf] > 0) {
            ans++;
        }
    }
}

void on (int nd) {
    upd(nd, 1);
}

void off (int nd) {
    upd(nd, -1);
}
/*********************GoodLuck***********************/
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i=2; i<=n; i++) {
        cin >> p[i];
        edge[p[i]].eb(i);
    }

    dfs_sz(1);
    dfs_ord(1, 1);

    REP1 (i, n) {
        int tmp;
        cin >> tmp;
        cnt[in[i]] -= tmp;
    }


    while (m--) {
        int d;
        cin >> d;

        state[in[abs(d)]] ^= 1;
        if (d < 0) {
            off(-d);
        } else {
            on(d);
        }

        cout << ans << " ";
    }
    cout << endl;
}
