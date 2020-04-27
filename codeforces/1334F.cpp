#include <bits/stdc++.h>
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
const ll MOD = 1000000007;

int n, m, v[MAXN], a[MAXN], b[MAXN];

ll dp[MAXN];

struct BIT {
    bool rev;
    ll bit[MAXN];
    BIT (bool _rev) {
        rev = _rev; 
        memset(bit, 0, sizeof(bit));
    }

    void add (int x, int val) {
        x++;
        if (rev) {
            x = n - x + 2;
        }
        for (;x<MAXN; x+=-x&x) {
            bit[x] += val;
        }
    }

    ll qry (int x) {
        ll res = 0;
        x++;
        if (rev) {
            x = n - x + 2;
        }
        for (;x>0; x-=-x&x) {
            res += bit[x];
        }
        return res;
    }
};

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> a[i];
    }
    a[n] = n+1;
    for (int i=0; i<n; i++) {
        cin >> v[i];
    }

    cin >> m;

    for (int i=1; i<=m; i++) {
        cin >> b[i];
    }
    b[m+1] = n+1;


    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    BIT pre(0);
    BIT suf(1);

    for (int i=0; i<=n; i++) {

        int c = lower_bound(b, b+m+2, a[i]) - b;

        ll gtp = suf.qry(b[c-1]+1);
        ll lep = pre.qry(b[c-1]);

        ll cdp = dp[c-1] + gtp + lep;
        debug(i, cdp);

        if (i < n) {
            suf.add(a[i], v[i]);
            pre.add(a[i], min(0,v[i]));

            gtp = suf.qry(b[c]+1);
            lep = pre.qry(b[c]);

            debug(gtp, lep);
            cdp = cdp - gtp - lep;
        }


        if (b[c] == a[i]) {
            dp[c] = min(dp[c], cdp);
            pary(dp, dp+m+2);
        }
    }

    if (dp[m+1] > 1e15) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << dp[m+1] << endl;
    }

}

