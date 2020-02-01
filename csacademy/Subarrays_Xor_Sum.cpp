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

int n, a, b, d[MAXN], p[MAXN];

struct Sum {
    int dt[MAXN];

    Sum () {
        memset(dt, 0, sizeof(dt));
    }

    void build () {
        for (int i=1;i<=n;i++) {
            dt[i] += dt[i-1];
        }
    }

    int qry (int l, int r) {
        return dt[r] - (l?dt[l-1]:0);
    }
} sum[31];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> a >> b;
    REP1 (i, n) {
        cin >> d[i];
        p[i] =p[i-1] ^ d[i];

        REP (j, 31) {
            sum[j].dt[i] += (p[i] >> j) & 1;
        }
    }
    REP (i, 31) {
        sum[i].build();
    }

    ll ans = 0;
    REP1 (i, n) {
        int l = max(0, i-b);
        int r = i-a;

        if (l <= r) {
            debug(i, l, r);
            REP (j, 31) {
                int cnt = sum[j].qry(l, r);
                if ((p[i]>>j)&1) {
                    cnt = r-l+1-cnt;
                }
                debug(cnt);

                ans += 1LL * cnt * (1LL<<j);
                ans %= MOD;
            }
        }
    }

    cout << ans << endl;
}
