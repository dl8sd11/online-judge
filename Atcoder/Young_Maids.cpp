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
const int INF = 0x3f3f3f3f;

int n, a[MAXN], pos[MAXN];
set<int> vis;
vector<int> ans;

int seg[MAXN*4][2], tag[MAXN*4];

int get (int o, int id) {
    return tag[o] ? seg[o][id^1] : seg[o][id];
}

void pull (int o) {
    seg[o][0] = min(get(o<<1, 0), get(o<<1|1, 0));
    seg[o][1] = min(get(o<<1, 1), get(o<<1|1, 1));
}

void push (int o) {
    if (tag[o]) {
        tag[o<<1] ^= 1;
        tag[o<<1|1] ^= 1;
        tag[o] = 0;
    }
}

void build (int o, int l, int r) {
    if (r == l + 1) {
        seg[o][l&1] = a[l];
    } else {
        int mid = (l + r) >> 1;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        pull(o);
    }
}

void flip (int qL, int qR, int o=1, int nL=0, int nR=n) {
    if (nL >= qR || qL >= nR || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] ^= 1;
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        flip(qL, qR, o<<1, nL, nM);
        flip(qL, qR, o<<1|1, nM, nR);
        pull(o);
    }
}

void chg (int x, int o=1, int nL=0, int nR=n) {
    if (nL > x || x >= nR) {
        return;
    } else if (nL == x && nR == x+1) {
        seg[o][0] = seg[o][1] = INF;
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        chg(x, o<<1, nL, nM);
        chg(x, o<<1|1, nM, nR);
        pull(o);
    }
}

int qry (int qL, int qR, int o=1, int nL=0, int nR=n) {
    if (nL >= qR || qL >= nR || qL >= qR) {
        return INF;
    } else if (qL <= nL && nR <= qR) {
        return tag[o] ? seg[o][1] : seg[o][0];
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        return min(qry(qL, qR, o<<1, nL, nM), qry(qL, qR, o<<1|1, nM, nR));
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    vis.insert(n);

    memset(seg, INF, sizeof(seg));
    build(1, 0, n);
    REP (i, n/2) {
        int pl = qry(0, n);
        ans.emplace_back(pl);
        pl = pos[pl];
        vis.insert(pl);
        int redg = *vis.lower_bound(pl+1);
        chg(pl);
        flip(pl+1, redg);

        int pr = qry(pl+1, redg);
        ans.emplace_back(pr);
        pr = pos[pr];
        vis.insert(pr);
        chg(pr);
        flip(pr+1, redg);

    }

    REP (i, n) {
        cout << ans[i] << " \n"[i==n-1];
    }


    return 0;
}
