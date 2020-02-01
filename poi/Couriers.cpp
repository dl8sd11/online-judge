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

const int MAXN = 300005;
const ll MOD = 1000000007;

int n, q, a[MAXN];

typedef pair<int,int> pii;
pii seg[MAXN*4];

pii mrg (const pii &p1, const pii &p2) {
    if (p1.first == p2.first) {
        return {p1.first, p1.second + p2.second};
    } else if (p1.second > p2.second) {
        return {p1.first, p1.second - p2.second};
    } else {
        return {p2.first, p2.second - p1.second};
    }
}

void pull (int o) {
    seg[o] = mrg(seg[o<<1], seg[o<<1|1]);
}

void build (int o, int l, int r) {
    if (r == l + 1) {
        seg[o] = {a[l], 1};
    } else {
        int m = (l + r) >> 1;
        build(o<<1, l, m);
        build(o<<1|1, m, r);
        pull(o);
    }
}

pii qry (int qL, int qR, int o, int nL, int nR) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return {0, 0};
    } else if (qL <= nL && nR <= qR) {
        return seg[o];
    } else {
        int nM = (nL + nR) >> 1;
        return mrg(qry(qL, qR, o<<1, nL, nM),
                   qry(qL, qR, o<<1|1, nM, nR));
    }
}

vector<int> pos[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q;
    REP (i, n) {
        cin >> a[i];
        pos[a[i]].emplace_back(i);
    }
    build(1, 0, n);

    while (q--) {
        int l, r;
        cin >> l >> r;

        int res = qry(l-1, r, 1, 0, n).first;
        int cnt = upper_bound(pos[res].begin(),pos[res].end(),r-1) - lower_bound(pos[res].begin(),pos[res].end(),l-1);
        debug(res, cnt);

        if (cnt > (r-l+1)/2) {
            cout << res << endl;
        } else {
            cout  << -1 << endl;
        }
    }
}
/*
7 5
1 1 3 2 3 4 3
1 3
1 4
3 7
1 7
6 6
*/
