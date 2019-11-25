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

const int MAXN = 100005;
const ll MOD = 1000000007;

ll n, k, f[MAXN];
vector<ll> p[MAXN];

void calc_sz (ll sz, ll rem, ll &sum) {
    if (sum >= k) {
        return;
    }
    if (sz != 0 && rem < p[sz-1][0]) {
        sz = upper_bound(f, f+sz, rem)-f;
    }
    if (sz == 0) {
        sum++;
        return;
    }
    calc_sz(sz-1, rem, sum);
    for (auto v : p[sz-1]) {
        if (rem >= v) {
            calc_sz(sz-1, rem-v, sum);
        }
    }
}

void solve (ll sz, ll rem, ll &sum) {
    if (sz != 0 && rem < p[sz-1][0]) {
        sz = upper_bound(f, f+sz, rem)-f;
    }
    if (sz == 0) {
        sum += rem + 1;
        return;
    }
    solve(sz-1, rem, sum);
    for (auto v : p[sz-1]) {
        if (rem >= v) {
            solve(sz-1, rem-v, sum);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
#ifndef tmd
    freopen("roboherd.in","r", stdin);
    freopen("roboherd.out", "w", stdout);
#endif

    cin >> n >> k;

    ll init = 0;
    REP (i, n) {
        ll sz;
        cin >> sz;

        vector<ll> vec(sz);
        REP (j, sz) {
            cin >> vec[j];
        }
        sort(vec.begin(), vec.end());

        init += vec[0];
        if (sz == 1) {
            i--;
            n--;
        }

        REP1 (j, sz-1) {
            p[i].emplace_back(vec[j]-vec[0]);
        }
    }

    sort(p, p+n);
    REP (i, n) {
        f[i] = p[i][0];
        #ifdef tmd
        for (auto v : p[i]) {
            cout << v << " ";
        }
        cout << endl;
        #endif
    }

    ll L = -1, R = 1000000LL*n;
    while (L < R - 1) {
        ll M = (L + R) >> 1;
        ll sum = 0;
        calc_sz(n, M, sum);
        debug(M, sum);
        if (sum >= k) {
            R = M;
        } else {
            L = M;
        }
    }
    debug(R);

    ll red = 0;
    solve(n, L, red);
    debug(red);

    cout << (init + R)*k - red << endl;

}
