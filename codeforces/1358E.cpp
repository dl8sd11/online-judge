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

const int MAXN = 1000005;
const ll MOD = 1000000007;

int n, a[MAXN], x;
ll sum[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    ll tmp = 0;
    REP (i, (n+1)/2) {
        cin >> a[i];
        tmp += a[i];
    }
    cin >> x;
    for (int i=(n+1)/2; i<n; i++) {
        a[i] = x;
    }
    pary(a, a+n);

    int len = n/2 + 1;
    if (tmp + n/2 * ll(x) > 0) {
        cout << n << endl;
        return 0;
    }

    tmp = 0;

    vector<ll> ans, pre;
    ll mn = 0x3f3f3f3f3f3f3f3f;
    for (int i=0; i<n; i++) {
        tmp += a[i];
        if (i-len >= 0) {
            tmp -= a[i-len];
        }
        if (i-len+1 >=0) {
            ans.eb(tmp);
            mn = min(mn, tmp);
            pre.eb(mn);
        }
    }

    ll sub = 0;

    ll res = -1;
    while (len <= n) {
        debug(pre, sub);
        if (pre.back() + sub > 0) {
            res = len;
        }
        pre.pop_back();
        sub += x;
        len++;
    }
    assert(pre.empty());

    cout << res << endl;

}

