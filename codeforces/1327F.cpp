#include <bits/stdc++.h>
#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("avx", "avx2", "fma")
using namespace std;
typedef long long ll;
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

const int MAXN = 500005;
const ll MOD = 998244353;

int n, k, m;
int l[MAXN], r[MAXN], x[MAXN];
vector<pii> led[MAXN], red[MAXN];

bool off[MAXN];

void add (int &X, int Y) {
    X = X + Y >= MOD ? X+Y-MOD : X+Y;
}

struct RSQ {

    int bit[MAXN], val[MAXN];
    RSQ () {
        memset(bit, 0, sizeof(bit));
        memset(val, 0, sizeof(val));
    }

    void chg (int p, int v) {
        val[p] = v;
        for (p++; p<MAXN; p+=-p&p) {
            add(bit[p], v);
        }
    }

    int qry (int p) {
        int res = 0;
        for (p++; p>0; p-=-p&p) {
            add(res, bit[p]);
        }
        return res;
    }
    int sum (int L, int R) {
        int res = qry(R) - qry(L-1);
        return res < 0 ? res+MOD : res;
    }
};

ll solve (int b) {

    int lst = -1;
    memset(off, 0, sizeof(off));
    for (int i=1; i<=n; i++) {
        for (auto p : led[i]) {
            if (p.Y & (1<<b)) {
                lst = max(lst, p.X);
            }
        }
        if (lst >= i) {
            off[i] = true;
        }
    }
    pary(off+1, off+n+1);

    RSQ dp;

    lst = 0;
    dp.chg(0, 1);
    for (int i=1; i<=n+1; i++) {
        if (!off[i]) {
            int cur = dp.sum(lst, i-1);
            dp.chg(i, cur);
        }
        for (auto p : red[i]) {
            if ((p.Y & (1<<b)) == 0) {
                debug(p.X , p.Y);
                lst = max(lst, p.X);
            }
        }
    }


    return dp.val[n+1];
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k >> m;
    for (int i=0; i<m; i++) {
        cin >> l[i] >> r[i] >> x[i];
        led[l[i]].eb(r[i], x[i]);
        red[r[i]].eb(l[i], x[i]);
    }

    int ans = 1;
    for (int i=0; i<k; i++) {
        ans = 1LL * ans * solve(i) % MOD;
    }
    cout << ans << endl;
}
