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

const int MAXN = 100005;
const ll MOD = 1000000007;
const int MAXD = 29;

int t;
int k, m, x[MAXN], tw[31];

int basis[31], sz;

void addVector (int x) {
    for (int i=MAXD; i>=0; i--) {
        if ((x >> i) & 1) {
            if (basis[i] == 0) {
                basis[i] = x;
                sz++;
                break;
            } else {
                x ^= basis[i];
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    tw[0] = 1;
    REP1 (i, 30) {
        tw[i] = tw[i-1] * 2;
    }

    cin >> t;
    while (t--) {
        cin >> k >> m;

        sz = 0;
        memset(basis, 0, sizeof(basis));

        REP (i, m) {
            cin >> x[i];
            addVector(x[i]);
        }

        cout << tw[k - sz] << endl;
    }
}
