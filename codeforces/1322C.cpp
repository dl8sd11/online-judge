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
const ll MOD[2] = {1000000007, 1000696969};

int t, n, m;
ll c[MAXN];
pair<int,int> hs[MAXN];
map<pair<int,int>, ll> sum;

ll mpow (ll base, ll ep, ll md) {
    ll ret = 1;
    while (ep) {
        if (ep&1) {
            ret = ret * base % md;
        }
        ep >>= 1;
        base = base * base % md;

    }
    return ret;
}

void nm (int &x, int md) {
    if (x >= md) {
        x -= md;
    }
}

void add (pair<int,int> &chg, pair<int,int> val) {
    chg.X += val.X;
    chg.Y += val.Y;
    nm(chg.X, MOD[0]);
    nm(chg.Y, MOD[1]);
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> t;
    while (t--) {
        cin >> n >> m;
        REP1 (i, n) {
            cin >> c[i];
            hs[i] = {0, 0};
        }
        sum.clear();
        REP (_u, m) {
            int u, v;
            cin >> u >> v;
            pair<int,int> res = {mpow(2,u,MOD[0]), mpow(3,u,MOD[1])};
            add(hs[v], res);
        }

        REP1 (i, n) {
            debug(hs[i].X, hs[i].Y);
            if (hs[i].X && hs[i].Y ) {
                sum[hs[i]] += c[i];
            }
        }
        
        ll ans = -1;
        for (const auto &p : sum) {
            if (ans == -1) {
                ans = p.Y;
            } else {
                ans = __gcd(ans, p.Y);
            }
        }

        cout << ans << endl;
    }


}

