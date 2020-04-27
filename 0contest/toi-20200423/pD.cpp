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

const int MAXN = 1300005;
const ll MOD = 1000000007;

vector<int> prime;
bool sieve[MAXN];
void build () {
    for (int i=2; i<MAXN; i++) {
        if (!sieve[i]) {
            prime.eb(i);
        }
        for (int j=0; j<SZ(prime) && prime[j]*i < MAXN; j++) {
            sieve[i*prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }

}
/*********************GoodLuck***********************/
int main () {
    IOS();

    build();
    pary(prime.begin(), prime.begin()+10);

    int d;
    while (cin >> d && d != 0) {
        auto nxt = lower_bound(ALL(prime), d);
        if (*nxt == d) {
            cout << 0 << endl;
        } else {
            cout << (*nxt) - (*prev(nxt)) << endl;
        }
        
    }


}

