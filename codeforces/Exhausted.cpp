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
const int iNF = 0x3f3f3f3f;

int n, m, ans, seg[MAXN * 4], tag[MAXN * 4];
vector<int> x[MAXN];

void push (int o) {
    if (tag[o]) {
        seg[o] += tag[o];
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        tag[o] = 0;
    }
}

int get (int o) {
    return seg[o] + tag[o];
}

void pull (int o) {
    seg[o] = max(get(o<<1), get(o<<1|1));
}

void build (int o, int l, int r) {
    if (r == l + 1) {
        seg[o] = -(m+1-l);
        tag[o] = 0;
    } else {
        int md = (l + r) >> 1;
        build(o<<1, l, md);
        build(o<<1|1, md, r);
        pull(o);
    }
}

int qry (int qL, int qR, int o=1, int nL=0, int nR=m+2) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return -iNF;
    } else if (qL <= nL && nR <= qR) {
        return get(o);
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        return max(qry(qL, qR, o<<1, nL, nM), qry(qL, qR, o<<1|1, nM, nR));
    }
}

void add (int qL, int qR, int o=1, int nL=0, int nR=m+2) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o]++;
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        add(qL, qR, o<<1, nL, nM);
        add(qL, qR, o<<1|1, nM, nR);
        pull(o);
    }
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    REP (i, n) {
        int l, r;
        cin >> l >> r;
        x[l].emplace_back(r);
    }

    ans = max(0, n-m);

    build(1, 0, m+2);
    REP (i, m+1) {
        for (auto r : x[i]) {
            add(0, r+1);
        }
        ans = max(ans, qry(i+2, m+2) - i);
    }

    cout << ans << endl;
    return 0;
}
