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

const int MAXN = 200005;
const ll MOD = 1000000007;

int k[3];
bitset<MAXN> problem[3];
int pre[MAXN], suf[MAXN];
int mnPre[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();
    REP (i, 3) {
        cin >> k[i];
    }

    REP (i, 3) {
        REP (j, k[i]) {
            int d;
            cin >> d;
            debug(i, d);
            problem[i][d] = true;
        }
    }

    int n = k[0] + k[1] + k[2];

    mnPre[0] = pre[0] = k[0];
    REP1 (i, n) {
        pre[i] = pre[i-1] - problem[0][i] + problem[1][i];
        mnPre[i] = min(mnPre[i-1], pre[i]);
    }

    suf[n+1] = k[2];
    for (int i=n; i>=1; i--) {
        suf[i] = suf[i+1] - problem[2][i] + problem[1][i];
    }

    int ans = MOD;
    for (int i=n+1; i>=1; i--) {
        ans = min(ans, suf[i]+mnPre[i-1]);
    }

    pary(pre, pre+n+1);
    pary(suf, suf+n+1);
    pary(mnPre, mnPre+n+1);

    cout << ans << endl;



}
