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
const ll MOD = (1LL<<61) - 1;

int t, n, k, a[MAXN];

inline void mad (ll &x, ll y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
}

ll dt[MAXN+1];
void init() {
    memset(dt, 0, sizeof(dt));
}

void add (int x, ll val) {
    for (x++; x<MAXN; x+=-x&x) {
        mad(dt[x], val);

    }
}

ll qry (int x) {
    ll ret = 0;
    for (x++; x>0; x-=-x&x) {
        mad(ret, dt[x]);
    }
    return ret;
}

int val[MAXN];
ll nxt[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();
    debug("HI");
    cin >> t;

    while (t--) {
        cin >> n >> k;

        REP (i, n) {
            #ifdef tmdd
            a[i] = rand();
            #else
            cin >> a[i];
            #endif
            val[i] = a[i];
        }

        sort(val, val+n);
        int sz = unique(val, val+n)-val;
        pary(val, val+sz);

        REP (i, n) {
            int L = -1, R = sz-1;
            while (L < R - 1) {
                int M = (L + R) >> 1;
                if (val[M] >= a[i]) {
                    R = M;
                } else {
                    L = M;
                }
            }
            a[i] = R + 1;
        }
        debug(sz);
        pary(a, a+n);

        memset(dt, 0, sizeof(dt));
        ll ans = 0;

        fill(nxt, nxt+n, 1);
        REP1 (j, k) {
            memset(dt, 0, sizeof(dt));
            REP (i, n) {
                add(a[i], nxt[i]);
                nxt[i] =  qry(a[i]-1);
            }
            mad(ans, qry(MAXN-2));

        }

        cout << ans << endl;
    }
}
