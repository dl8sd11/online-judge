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

const int MAXN = 5003;
const ll MOD = 1000000007;

int n, x[MAXN], y[MAXN];
struct Edge {
    short u, v, w;
    bool operator < (const Edge & oth) const {
        return w > oth.w;
    }
} edge[MAXN*MAXN];

int mah (int i, int j) {
    return (x[i]>x[j] ? x[i]-x[j] : x[j]-x[i]) + (y[i]>y[j] ? y[i]-y[j] : y[j]-y[i]);
}

ll mpow (ll bs, ll ep) {
    ll ret = 1;
    while (ep) {
        if (ep&1) {
            ret = ret * bs % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return ret;
}

int djs[MAXN*2], sz[MAXN*2], comp;
bool valid;

void init () {
    REP (i, n*2) {
        djs[i] = i;
        sz[i] = 1;
    }
    comp = n*2;
    valid = true;
}

int fnd (int nd) {
    return djs[nd] == nd ? nd : djs[nd] = fnd(djs[nd]);
}

void uni (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x == y) {
        return;
    }
    comp--;
    if (sz[x] > sz[y]) {
        swap(x, y);
    }
    djs[x] = y;
    sz[y] += sz[x];
}

void mrg (int x, int y) {
    uni(x*2, y*2+1);
    uni(x*2+1, y*2);
    if (fnd(x*2) == fnd(x*2+1)) {
        valid = false;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    init();

    int cnt = 0;
    REP (i, n) {
        cin >> x[i] >> y[i];
        REP (j, i) {
            edge[cnt++] = {j, i, mah(i, j)};
        }
    }

    sort(edge, edge+cnt);

    int ans = 0, cob, idx = 0;
    for (int i=MAXN*2; i>=0; i--) {
        while (idx < cnt && edge[idx].w > i) {
            mrg(edge[idx].u, edge[idx].v);
            pary(djs, djs+n);
            debug(i, edge[idx].u, edge[idx].v, edge[idx].w);
            idx++;
        }
        if (!valid) {
            break;
        }
        ans = i;
        cob = mpow(2, comp/2);
    }

    cout << ans << endl << cob << endl;


}
