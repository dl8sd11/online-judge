#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define SQ(i) ((i)*(i))
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 1003;

int m, n, k, x[MAXN], y[MAXN], r[MAXN], djs[MAXN], mnx[MAXN], mny[MAXN], mxx[MAXN], mxy[MAXN];

int fnd (int v) {
    return v == djs[v] ? v : djs[v] = fnd(djs[v]);
}

void mrg (int v, int u) {
    v = fnd(v), u = fnd(u);
    djs[v] = u;
    mnx[u] = min(mnx[v], mnx[u]);
    mxx[u] = max(mxx[v], mxx[u]);
    mny[u] = min(mny[v], mny[u]);
    mxy[u] = max(mxy[v], mxy[u]);
}
/****GOOD_LUCK****/
int main () {
    IOS();

    cin >> m >> n >> k;
    REP (i, k) {
        cin >> x[i] >> y[i] >> r[i];
        djs[i] = i;
        mnx[i] = x[i] - r[i], mxx[i] = x[i] + r[i];
        mny[i] = y[i] - r[i], mxy[i] = y[i] + r[i];
        REP (j, i) {
            if (SQ(x[i]-x[j]) + SQ(y[i]-y[j]) <= SQ(r[i]+r[j])) {
                mrg(i, j);
            }
        }
    }

    bool ans = true;
    REP (i, k) {
        int cur = fnd(i);
        if (mxy[cur] >= n) {
            if (mxx[cur] >= m) {
                ans = false;
            } else if (mny[cur] <= 0) {
                ans = false;
            }
        }
        if (mnx[cur] <= 0) {
            if (mxx[cur] >= m) {
                ans = false;
            } else if (mny[cur] <= 0) {
                ans = false;
            }
        }
    }

    cout << (ans ? "S" : "N") << endl;
    return 0;
}
