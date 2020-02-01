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
template<typename T> ostream &operator << (ostream &os,pair<T,T> &v){return os<<v.first<<","<<v.second;}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1000006;
const ll MOD = 1000000007;

int n, k, l;
bool s[MAXN];

ll dp[MAXN], chg[MAXN];
pair<ll,ll> cost (ll p) { // {x, f(x)-px}
    for (ll i=1;i<=n;i++) {
        dp[i] = dp[i-1] + s[i];
        chg[i] = chg[i-1];
        if (i>=l) {
            if (dp[i-l]+l-p > dp[i]) {
                dp[i] = dp[i-l]+l-p;
                chg[i] = chg[i-l]+1;
            }
        } else {
            if (i-p > dp[i]) {
                dp[i] = i-p;
                chg[i] = 1;
            }
        }
    }
    return {chg[n], dp[n]};
}

int solve () {
    pair<ll,ll> c0 = cost(0);
    debug(c0);
    if (c0.first <= k) {
        return c0.second;
    }
    ll L = l+1, R = 0;
    while (R < L - 1) {
        ll M = (L + R) >> 1;
        pair<ll,ll> res = cost(M);
        if (res.first > k) {
            R = M;
        } else {
            L = M;
        }
    }

    pair<ll,ll> Lres, Rres;
    Lres = cost(L);
    Rres = cost(R);
    Lres.second += Lres.first * L;
    Rres.second += Rres.first * R;

    for (int i=0;i<=l+1;i++) {
        debug(i, cost(i));
    }

    if (Lres.first == k) {
        return Lres.second;
    } else {
        debug(Lres, Rres);
        ll a = k-Lres.first;
        ll b = Rres.first-k;
        return (a*Rres.second+b*Lres.second)/(a+b);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> k >> l;

    REP1 (i, n) {
        char c;
        cin >> c;
        s[i] = islower(c);
    }

    int ans = solve();
    REP1 (i, n) {
        s[i] = !s[i];
    }
    ans = max(ans, solve());

    cout << n-ans << endl;
}
