#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
vector<int> a, b;
set<int> aval;

vector<int> pre, suf;

struct Node {
    int L, R, M;
} seg[MAXN*4];

void build_seg (int l, int r, int o) {
    if (l == r - 1) {
        seg[o] = {0, 0 ,0};
    } else {
        int m = (l + r) >> 1;
        seg[o] = {0, 0, 0};
        build_seg(l, m, o<<1);
        build_seg(m, r, o<<1|1);
    }
}

void pull (int o) {
    seg[o].M = seg[o<<1].M + seg[o<<1|1].M;
    if (seg[o<<1].L > seg[o<<1|1].R) {
        seg[o].M += seg[o<<1|1].R;
        seg[o].L = seg[o<<1].L - seg[o<<1|1].R + seg[o<<1|1].L;
        seg[o].R = seg[o<<1].R;
    } else {
        seg[o].M += seg[o<<1].L;
        seg[o].R = seg[o<<1].R + seg[o<<1|1].R -seg[o<<1].L;
        seg[o].L = seg[o<<1|1].L;
    }
}

void ins (int pos, bool left, int o, int nL, int nR) {
    if (pos >= nR || pos < nL) {
        return;
    } else if (nL == pos && nR == pos + 1) {
        if (left) {
            seg[o].L = 1;
        } else {
            seg[o].R = 1;
        }
    } else {
        int nM = (nL + nR) >> 1;
        ins(pos, left, o<<1, nL, nM);
        ins(pos, left, o<<1|1, nM, nR);
        pull(o);
    }
}

void build(vector<int> &ret) {
    build_seg(0, n*2, 1);
    ret.emplace_back(0);
    REP (i, n) {
        ins(a[i], true, 1, 0, n*2);
        ins(b[n-i-1], false, 1, 0, n*2);
        debug(i, a[i], b[n-i-1]);
        ret.emplace_back(seg[1].M);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    #ifndef tmd

    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);

    #endif // tmd

    cin >> n;
    REP (i, n) {
        int d;
        cin >> d;
        a.emplace_back(d-1);
        aval.insert(d-1);
    }

    REP (i,n*2) {
        if (aval.count(i) == 0) {
            b.emplace_back(i);
        }
    }

    debug(a);
    debug(b);

    build(pre);

    REP (i, n) {
        a[i] = n*2 - a[i] - 1;
        b[i] = n*2 - b[i] - 1;
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    build(suf);
    debug(pre);
    debug(suf);

    int ans = 0;
    REP (i, n+1) {
        ans = max(ans, pre[i]+suf[n-i]);
    }

    cout << ans << endl;

}
