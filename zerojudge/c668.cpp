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
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1000006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int T, mn, mx;
ll mpow (ll bs, int ep, ll md) {
    ll ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = ret * bs % md;
        }
        bs = bs * bs % md;
        ep >>= 1;
    }
    return ret;
}


vector<int> test = {2, 7, 61};
bool notPrime (ll a, ll p) {
    if (p % 2 == 0) {
        return p != 2;
    }
    int u = p - 1, t = 0;
    while (u%2 == 0) {
        u /= 2;
        t++;
    }

    ll cur = mpow(a, u, p);
    if (cur == 1 || cur == p -1) {
        return false;
    } else {
        REP (i, t-1) {
            cur = cur * cur % p;
            if (cur == p-1) {
                return false;
            } else if (cur == 1) {
                return true;
            }
        }
        return !((cur == 1 || cur == -1) && (cur * cur % p == 1));
    }
}

bool isPrime (ll p) {
    for (auto seed : test) {
        if (notPrime(seed, p)) {
            debug(p, seed);
            return false;
        }
    }
    return true;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> T >> mn >> mx;

    ll n;
    while (T--) {
        cin >> n;
        ll p;

        ll k = n/6;
        for (;;k++) {
            if (k*6-1 > n && isPrime(k*6-1)) {
                p = k*6-1;
                break;
            }
            if (k*6+1 > n && isPrime(k*6+1)) {
                p = k*6+1;
                break;
            }
        }
        if (n < 10) {
            for (k=n+1;;k++) {
                if (isPrime(k)) {
                    p = k;
                    break;
                }
            }
        }
        cout << p << endl;
    }
}
