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
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

int n, m, a[MAXN];
typedef pair<int, int> pii;
typedef array<pii, 10> ap10;
ap10 seg[MAXN*4];

ap10 mrg (const ap10 &l, const ap10 &r) {
    ap10 ret;
    REP (i, 10) {
        array<int,4> sa = {l[i].first, l[i].second, r[i].first, r[i].second};
        sort(sa.begin(), sa.end());
        ret[i] = {sa[0], sa[1]};
    }
    return ret;
}

void pull (int o) {
    seg[o] = mrg(seg[o<<1], seg[o<<1|1]);
}
void build (int o, int l, int r) {
    if (r == l + 1) {
        int x = a[l];
        REP (i, 10) {
            seg[o][i] = {INT_MAX, INT_MAX};
            if (x % 10) {
                seg[o][i].first = a[l];
            }
            x /= 10;
        }
    } else {
        int mid = (l + r) >> 1;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        pull(o);
    }
}

void chg (int p, int val, int o=1, int nL=0, int nR=n) {
    if (p >= nR || p < nL) {
        return;
    } if (nL == p && nR == p + 1) {
        int x = val;
        REP (i, 10) {
            seg[o][i] = {INT_MAX, INT_MAX};
            if (x % 10) {
                seg[o][i].first = val;
            }
            x /= 10;
        }
    } else {
        int nM = (nL + nR) >> 1;
        chg(p, val, o<<1, nL, nM);
        chg(p, val, o<<1|1, nM, nR);
        pull(o);
    }
}

ap10 qry (int qL, int qR, int o=1, int nL=0, int nR=n) {
    ap10 ret;
    REP (i, 10) {
        ret[i] = {INT_MAX, INT_MAX};
    }
    if (qL >= nR || qR <= nL || qL >= qR) {
        return ret;
    } else if (qL <= nL && nR <= qR) {
        return seg[o];
    } else {
        int nM = (nL + nR) >> 1;
        return mrg(qry(qL, qR, o<<1, nL, nM), qry(qL, qR, o<<1|1, nM, nR));
    }
}


/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n) {
        cin >> a[i];
    }

    build(1, 0, n);

    REP (u, m) {
        int cmd, A, b;
        cin >> cmd >> A >> b;
        if (cmd == 1) {
            chg(A-1, b);
        } else {
            ap10 ret = qry(A-1, b);
            int ans = INT_MAX;
            REP (i, 10) {
                if (ret[i].second != INT_MAX) {
                    ans = min(ans, ret[i].first + ret[i].second);
                }
            }

            cout << (ans == INT_MAX ? -1 : ans) << endl;
        }
    }
    return 0;
}
