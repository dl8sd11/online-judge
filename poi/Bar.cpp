#include <bits/stdc++.h>
#pragma GCC optimize("O3","unroll-loops")
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

const int MAXN = 1000005;
const ll MOD = 1000000007;


int n, a[MAXN], pre[MAXN], ans;
typedef pair<int,int> pii;
set<pii> rk;
int l[MAXN], r[MAXN];

void solve (int *res, bool rev) {
    rk.clear();

    int sum = 0;
    for (int i=0; i<n; i++) {
        sum += a[i];
        pre[i] = sum;
        rk.insert(pii(sum, -i));
    }

    sum = 0;
    for (int i=0; i<n; i++) {
        auto ptr = rk.upper_bound(pii(sum, -n));
        int cur = n - 1;
        if (ptr != rk.begin()) {
            cur = -(prev(ptr)->second) - 1;
        }

        if (rev) {
            res[n-1-i] = n-1-cur;
        } else {
            res[i] = cur;
        }

        sum += a[i];
        rk.erase(pii(sum, -i));
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    scanf(" %d",&n);
    getchar();

    REP (i, n) {
        char c;
        c = getchar();
        a[i] = c == 'j' ? -1 : 1;
    }

    solve(l, false);
    reverse(a, a+n);
    solve(r, true);

    pary(l, l+n);
    pary(r, r+n);

    set<int> R;
    vector<pii> rV;
    REP (i, n) {
        rV.emplace_back(r[i], i);
    }
    sort(rV.begin(), rV.end());

    int ptr = 0;
    for (int i=0; i<n; i++) {
        while (ptr < n && rV[ptr].first <= i) {
            R.insert(rV[ptr].second);
            ptr++;
        }

        auto ptr = R.upper_bound(l[i]);
        if (ptr != R.begin()) {
            ans = max(ans, *prev(ptr) - i + 1);
        }
    }

    printf("%d\n",ans);

}
