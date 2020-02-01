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

const int MAXN = 302;
const ll MOD = 998244353;

int n, m;
ll tw[MAXN];
bitset<MAXN> rw[MAXN];

bitset<MAXN> basis[MAXN];
int sz;

void inc (bitset<MAXN> vec) {
    for (int i=MAXN-1; i>=0; i--) {
        if (vec[i]) {
            if (basis[i].count() == 0) {
                basis[i] = vec;
                sz++;
                break;
            } else {
                vec ^= basis[i];
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    tw[0] = 1;
    REP1 (i, MAXN-1) {
        tw[i] = tw[i-1] * 2 % MOD;
    }

    cin >> n >> m;
    REP (i, n) {
        REP (j, m) {
            bool d;
            cin >> d;
            rw[i][j] = d;
        }

        inc(rw[i]);
    }

    int free = n - sz;
    ll rcob = tw[n] - tw[free];
    if (rcob < 0) {
        rcob += MOD;
    }

    cout << rcob * tw[m-1] % MOD << endl;
}
