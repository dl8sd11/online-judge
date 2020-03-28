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
const int MAXLG = __lg(MAXN) + 2;
const ll MOD = 1000000007;

int n;
vector<int> edge[MAXN];

bool dead[MAXN];
int sz[MAXN];

void dfsSZ (int nd, int par) {
    sz[nd] = 1;
    for (auto v : edge[nd]) {
        if (v != par && !dead[v]) {
            dfsSZ(v, nd);
            sz[nd] += sz[v];
        }
    }
}

int FULL;
pii dfsCen (int nd, int par) {
    pii res = {MOD, nd};

    int mx = FULL - sz[nd];
    for (auto v : edge[nd]) {
        if (v != par && !dead[v]) {
            pii cur = dfsCen(v, nd);
            res = min(res, cur);
            mx = max(mx, sz[v]);
        }
    }
    if (mx < res.X) {
        res = {mx, nd};
    }
    return res;
}

int dis[MAXLG][MAXN];
int pa[MAXN], lv[MAXN];

void buildCen (int nd, int par, int lev, int d) {
    dis[lev][nd] = d;
    for (auto v : edge[nd]) {
        if (v != par && !dead[v]) {
            buildCen(v, nd,lev, d+1);
        }
    }
}

void CentroidDecomp (int root, int lev, int prv) {
    dfsSZ(root, -1);
    FULL = sz[root];
    int cen = dfsCen(root, -1).Y;
    pary(sz+1,sz+n+1);
    debug(cen, prv, lev);

    dead[cen] = true;
    pa[cen] = prv;
    lv[cen] = lev;
    buildCen(cen, cen, lev, 0);

    for (auto v : edge[cen]) {
        if (!dead[v]) {
            CentroidDecomp(v, lev+1, cen);
        }
    }
}

bool on[MAXN];
priority_queue<pii, vector<pii>, greater<pii> > cenMn[MAXN];

int getMin (int nd) {
    while (cenMn[nd].size()) {
        const pii &tp = cenMn[nd].top();
        debug(tp.X, tp.Y, on[tp.Y]);
        if (!on[tp.Y]) {
            cenMn[nd].pop();
        } else {
            break;
        }
    }

    return cenMn[nd].empty() ? MOD : cenMn[nd].top().X;
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n-1) {
        int u, v;
        #ifdef tmdd
        u = i + 2;
        v = rand() % (i + 1) + 1;
        #else
        cin >> u >> v;
        #endif // tdm
        edge[u].eb(v);
        edge[v].eb(u);
    }

    CentroidDecomp(1, 0, 0);

    int q;
    cin >> q;

    int cnt = 0;
    while (q--) {
        int cmd, nd;
        #ifdef tmdd
        cmd = rand() % 2;
        nd = rand() % n + 1;
        #else
        cin >> cmd >> nd;
        #endif // tmd
        if (cmd == 0) { // change
            int cen = nd;
            while (cen != 0) {

//                debug(cen, dis[lv[cen]][nd]);
                if (!on[nd]) {
                    cenMn[cen].emplace(dis[lv[cen]][nd], nd);
                }

                cen = pa[cen];
            }
            if (on[nd]) {
                cnt--;
            } else {
                cnt++;
            }
            on[nd] ^= 1;
        } else {
            int cen = nd;

            int ans = MOD;
            while (cen != 0) {

                int mn = getMin(cen);
                mn += dis[lv[cen]][nd];
//                debug(cen, mn);

                ans = min(ans, mn);
                cen = pa[cen];
            }

            cout << (cnt == 0 ? -1 : ans) << endl;

        }
    }
}
