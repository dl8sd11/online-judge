#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
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

const int MAXN = 50004;
const ll MOD = 1000000007;

int n, K, a[MAXN], q;

namespace SMALL {
    ll dp[21];
    int ans[1003][1003];

    void build () {
        for (int l=1; l<=n; l++) {
            memset(dp, 0, sizeof(dp));
            for (int r=l; r<=n; r++) {
                ll sum = 1;

                int x = a[r];
                for (int k=1; k<=x; k++) {
                    sum = (sum + dp[k]) % MOD;
                }
                dp[x] = (dp[x] + sum) % MOD;

                ll res = 0;
                for (int k=1; k<=K; k++) {
                    res = (res + dp[k]) % MOD;
                }

                ans[l][r] = res;
            }
        }
    }
};

void add (int &x, const int y) {
    x = x + y >= MOD ? x + y - MOD : x + y;
}

typedef array<array<int,21>,21> state;
namespace MED {

    state seg[MAXN*2];

    state mrg (const state &sl, state sr) {
        state res = {};

        for (int l=1;l<=K;l++) {
            for (int r=l;r<=K;r++) {
                add(res[l][r], sl[l][r]);
                add(res[l][r], sr[l][r]);
            }
        }
        for (int r=1; r<=K; r++) {
            for (int l=r-1;l>=1; l--) {
                add(sr[l][r], sr[l+1][r]);
            }
        }

        for (int i=1; i<=K; i++) {
            for (int j=i; j<=K; j++) {
                for (int k=i; k<=j; k++) {
                    add(res[i][j], 1LL*sl[i][k]*sr[k][j]%MOD);
                }
            }
        }

        return res;
    }

    void build () {
        REP (i, n) {
            seg[i+n] = {};
            seg[i+n][a[i+1]][a[i+1]] = 1;
        }
        for (int i=n-1; i>0; i--) {
            seg[i] = mrg(seg[i<<1], seg[i<<1|1]);
        }
    }

    int qry (int l, int r) {
        state res = {};

        vector<int> ln, rn;
        for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l&1) {
                ln.eb(l++);
            }
            if (r&1) {
                rn.eb(--r);
            }
        }
        for (auto v : ln) {
            res = mrg(res, seg[v]);
        }
        for (auto it=rn.rbegin(); it!=rn.rend(); it++) {
            res = mrg(res, seg[*it]);
        }

        int ans = 0;
        REP1 (i, K) {
            for (int j=i; j<=K; j++) {
                add(ans, res[i][j]);
            }
        }

        return ans + 1;
    }
};

/*********************GoodLuck***********************/
int main () {
    IOS();


    #ifndef tmd

    freopen("nondec.in", "r", stdin);
    freopen("nondec.out", "w", stdout);

    #endif // tmd

    cin >> n >> K;
    REP1 (i, n) {
        cin >> a[i];
    }

    if (n <= 1000) {
        SMALL::build();

        cin >> q;
        while (q--) {
            int l, r;
            cin >> l >> r;
            cout << SMALL::ans[l][r] + 1<< endl;
        }
    } else {
        MED::build();

        cin >> q;
        while (q--) {
            int l, r;
            cin >> l >> r;
            cout << MED::qry(l-1, r) << endl;
        }
    }

}
