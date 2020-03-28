#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
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

int n, l, w;
vector<int> lft, rgt;

bool solve (int A, int B) {
    if (A < 0 && 0 < A + l) {
        return true;
    }
    if (A >= 0) {
        return ll(w-1)*(B-A+l)>abs(A)*2;
    } else {
        return ll(w+1)*(B-A+l)>abs(A)*2;
    }
}
/*********************GoodLuck***********************/
signed main () {
    IOS();

    cin >> n >> l >> w;
    REP (i, n) {
        int x, v;
        cin >> x >> v;
        if (v == 1) {
            lft.eb(x);
        } else {
            rgt.eb(x);
        }
    }
    sort(ALL(lft));
    sort(ALL(rgt));

    int idx = 0;
    ll ans = 0;
    for (auto x : lft) {
        while (idx < SZ(rgt) && rgt[idx] < x) {
            idx++;
        }
        int L = idx-1, R = SZ(rgt);
        while (L < R - 1) {
            int M = (L + R) >> 1;
            bool res = solve(x, rgt[M]);
            debug(x, rgt[M], res);
            if (res) {
                R = M;
            } else {
                L = M;
            }
        }

        ans += SZ(rgt) - R;
    }

    #ifdef tmd

    int aans = 0;
    for (auto l : lft) {
        for (auto r : rgt) {
            if (l < r) {
                aans += solve(l, r);
                if (solve(l, r)) {
                    debug(l, r);
                }
            }
        }
    }
    debug(aans, ans);
    assert(aans == ans);

    #endif // tme

    cout << ans << endl;
}
