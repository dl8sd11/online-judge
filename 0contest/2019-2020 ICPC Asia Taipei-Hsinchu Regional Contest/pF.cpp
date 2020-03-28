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

const int MAXN = 1000006;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1000000007;
const int MAXC = 12;
ll n, k, a[MAXN], e[MAXN];

vector<array<ll,3> > cost;
vector<ll> dv;
vector<int> pmsk[MAXN];

void builddv (ll val) {
    for (int i=2; i*i<val; i++) {
        if (val % i == 0) {
            dv.eb(i);
            while (val % i == 0) {
                val /= i;
            }
        }
    }
    if (val > 1) {
        dv.eb(val);
    }
    debug(dv);
}

priority_queue<pll> bst[1<<MAXC];

ll dp[MAXC][1<<MAXC];
/*********************GoodLuck***********************/
signed main () {
    IOS();

    cin >> n >> k;
    ll gcd;
    REP (i, n) {
        cin >> a[i];
        if (i > 0) {
            gcd = __gcd(gcd, a[i]);
        } else {
            gcd = a[i];
        }
    }
    builddv(gcd);
    int sz = SZ(dv);

    REP (i, n) {
        cin >> e[i];
        ll rem = 1, tmp = a[i];
        for (auto p : dv) {
            while (tmp % p == 0) {
                tmp /= p;
                rem *= p;
            }
        }
        cost.push_back({rem, e[i], i});
    }

    sort(ALL(cost));

    ll pw[1<<MAXC];
    pw[0] = 1;
    for (int l=0,r=0; l<n; l=r) {
        while (r<n && cost[l][0] == cost[r][0]) {
            r++;
        }
        for (int i=0; i<sz; i++) {
            ll x = 1, tmp = cost[l][0];
            while (tmp % dv[i] == 0) {
                x *= dv[i];
                tmp /= dv[i];
            }
            for (int msk=0; msk<(1<<i); msk++) {
                pw[msk|(1<<i)] = pw[msk] * x;
            }
        }
        for (int msk=0; msk<(1<<sz); msk++) {
            if (pw[msk] <= k) {
                for (int i=l; i<min(r,l+sz); i++) {
                    bst[msk].emplace(cost[i][1], cost[i][2]);
                    if (SZ(bst[msk]) > sz) {
                        bst[msk].pop();
                    }
                }
            }
        }
    }

    for (int msk=0; msk<(1<<sz); msk++) {
        while (bst[msk].size()) {
            pmsk[bst[msk].top().Y].eb(msk);
            bst[msk].pop();
        }
    }



    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int i=0; i<n; i++) {
        for (int j=sz; j>=1; j--) {
            for (auto msk : pmsk[i]) {
                int imsk = ((1<<sz)-1)^msk;

                dp[j][msk] = min(dp[j-1][0] + e[i], dp[j][msk]);
                for (int smsk=imsk; smsk>0; smsk = (smsk-1)&imsk) {
                    dp[j][smsk|msk] = min(dp[j-1][smsk]+e[i], dp[j][smsk|msk]);
                }
            }
        }
    }

    ll ans = INF;
    REP (i, sz+1) {
        if (dp[i][(1<<sz)-1] != INF) {
            ans = min(ans, i*dp[i][(1<<sz)-1]);
        }
    }

    cout << (ans == INF ? -1 : ans) << endl;


}
/*
3 6
30 30 30
100 4 5
*/
