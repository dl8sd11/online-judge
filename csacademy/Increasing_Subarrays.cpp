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
template<typename T> ostream &operator << (ostream &os,deque<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1000005;
const ll MOD = 1000000007;

int n;
ll m;
int a[MAXN];

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n) {
        cin >> a[i];
    }

    ll ans = 0, sum = 0;
    deque<int> deq;

    for (int l=n-1,r=n-1;l>=0;l--) {
        while (deq.size() && a[deq[0]] < a[l]) {
            int x = deq[0];
            if (deq.size() == 1) {
                sum += (r+1-x) * (a[l]-a[x]);
            } else {
                sum += (deq[1]-x) * (a[l]-a[x]);
                debug((deq[1]-x), (a[l]-a[x]));
            }
            deq.pop_front();
        }
        deq.emplace_front(l);

        debug(deq, sum);
        while (sum > m) {
            debug(sum, m);
            sum -= a[deq.back()] - a[r];
            if (deq.back() == r) {
                deq.pop_back();
            }
            r--;
        }

        debug(l, r, sum);
        ans += r - l + 1;
    }

    cout << ans << endl;
}
