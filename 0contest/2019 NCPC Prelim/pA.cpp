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

const int MAXN = 100005;
const ll MOD = 1000000007;

int m;
ll n;

set<pair<ll,ll> > st;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> m;
    while (m--) {
        cin >> n;
        st.clear();

        ll x = 3;
        ll p = 1;

        bool isP = true;
        for (ll j=2;j*j<n; j++) {
            if (n%j == 0) {
                isP = false;
            }
        }

        if (!isP) {
            for (int i=2; ; i++) {
                if (i & 1) {
                    x = (5*x + 3) % n;
                } else {
                    x = n-x;
                }
                if (st.count({x, i&1})) {
                    break;
                }
                st.insert({x,i&1});

                ll gcd = x > 0 ? __gcd(n, x) : 0;
                if (1 < gcd && gcd < n) {
                    p = gcd;
                    break;
                }
            }
        }

        cout << n << " = " << p << " * " << n/p << endl;
    }
}
