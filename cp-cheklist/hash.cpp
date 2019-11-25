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

string a, b;

#define ull unsigned long long

const ull C = 1000;
ull CN[MAXN];

int mat () {
    int ret = 0;
    CN[0] = 1;
    REP1 (i, MAXN-1) {
        CN[i] = CN[i-1] * C;
    }

    ull ha = 0;
    for (auto c : a) {
        ha += c;
        ha *= C;
    }

    int n = SZ(a);
    ull hb = 0;
    REP (i, SZ(b)) {
        if (i >= n) {
            hb = hb - (b[i-n]) * CN[n];
        }
        hb += b[i];
        hb *= C;
        if (i >= n-1) {
            ret += hb == ha;
            debug(ha, hb);
        }
    }

    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> a >> b;

    cout << mat() << endl;
}
