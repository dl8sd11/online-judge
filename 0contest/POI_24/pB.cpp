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
const int K = 300;

int n, q, a[MAXN];
int pre[301][MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q;
    while (q--) {
        int x, d, l;
        cin >> x >> d >> l;

        if (l < K) {
            pre[l][x]++;

            if (x+l*d <= n) {
                pre[l][x+l*d]--;
            }
        } else {
            REP (i, d) {
                a[x+i*l]++;
            }
        }
    }

    REP (i, K) {
        REP1 (j, n) {
            if (j >= i) {
                pre[i][j] += pre[i][j-i];
            }
            a[j] += pre[i][j];
        }
    }

    REP1 (i, n) {
        cout << a[i] << " \n"[i==n];
    }
}
