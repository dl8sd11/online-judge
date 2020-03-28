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

const int MAXN = 2000006;
const ll MOD = 1000000009;
const ll B = 880301;

int n;
string str;

ll hsum[MAXN], bs[MAXN], ib[MAXN];

ll mpow (ll bb, ll ep) {
    ll ret = 1;
    while (ep) {
        if (ep&1) {
            ret = ret * bb % MOD;
        }
        bb = bb * bb % MOD;
        ep >>= 1;
    }
    return ret;
}

void build () {
    ll iB = mpow(B, MOD-2);
    bs[0] = ib[0] = 1;
    for (int i=1; i<MAXN; i++) {
        bs[i] = bs[i-1] * B % MOD;
        ib[i] = ib[i-1] * iB % MOD;
    }

    for (int i=0; i<n; i++) {
        debug(str[i], bs[i]);
        hsum[i+1] = (hsum[i] + bs[i] * str[i]) % MOD;
    }

}

ll sub (int l, int r, int lift) {
    debug(l, r, lift);
    ll ha = hsum[r+1] - hsum[l];
    ha = ha * ib[l] % MOD;
    ha = ha * bs[lift] % MOD;
    ha = ha > 0 ? ha : ha + MOD;
    return ha;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> str;
    if (n & 1 ^ 1) {
        cout << "NOT POSSIBLE" << endl;
        return 0;
    }
    build();

    set<ll> S;
    int rmv = -1;

    const int n2 = n/2;
    for (int i=0; i<n; i++) {
        ll lh = i < n2 ? (sub(0,i-1,0) + sub(i+1, n2, i)) % MOD : sub(0, n2-1, 0);
        ll rh = i > n2 ? (sub(n2,i-1,0) + sub(i+1, n-1, i-n2)) % MOD : sub(n2+1, n-1, 0);

        debug(i, lh, rh);
        if (lh == rh) {
            S.insert(lh);
            rmv = i;
        }
    }

    if (S.empty()) {
        cout << "NOT POSSIBLE" << endl;
    } else if (SZ(S) >= 2) {
        cout << "NOT UNIQUE" << endl;
    } else {
        cout << (rmv >= n2 ? str.substr(0,n2) : str.substr(n2+1, n2)) << endl;
    }

}
