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


const int MAXN = 1002;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll f[MAXN], sum[MAXN], ovg[MAXN];
ll bad[102];
/*********************GoodLuck***********************/
int main () {
    IOS();

    memset(f, INF,sizeof(f));
    f[1] = 1;
    f[0] = 0;

    ll lim = 11;
    ll lf = lim * (lim+1) * (2*lim+1) / 6;

    for (int i=1;i<MAXN; i++) {
        for (int j=1;j*j<=i;j++) {
            if (f[i-j*j] < j) {
                f[i] = j;
                break;
            }
        }
    }

    int bcnt = 0;
    REP1 (i, MAXN-1) {
        for (int j=i+1;j<MAXN;j++) {
            if (f[j] < f[i]) {
                ovg[i] = true;
                break;
            }
        }
        if (f[i] == INF) {
            bad[bcnt++] = i;
        }
        sum[i] = sum[i-1] + ovg[i];
    }
    pary(bad, bad+bcnt);

    ll n;
    cin >> n;
    if (n <= lf) {
        if (f[n] == INF) {
            cout << "- " << sum[n] << endl;
        } else {
            cout << f[n] << " " << sum[n] << endl;
        }
    } else {

        ll ssum = 0, x;
        for (x=1;x<n;x++) {
            ssum += x * x;
            if (ssum >= n) {
                break;
            }
        }

        pair<ll,ll> ans = {x, 0};
        REP (i, bcnt) {
            if (ssum-bad[i]==n) {
                ans.first = x + 1;
            }
        }

        ans.second = sum[lf] + (bcnt) * (x-lim-1);
        REP (i, bcnt) {
            if (ssum-bad[i]<=n) {
                ans.second++;
            }
        }

        debug(lim, lf, f[n], sum[n]);
        cout << ans.first << " " << ans.second;

    }
}
