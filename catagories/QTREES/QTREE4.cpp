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
template<typename T> ostream &operator << (ostream &os,pair<T,T> &v){return os<<"{"<<v.X<<","<<v.Y<<"}";}
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
int xr[MAXN], w[MAXN], sz[MAXN];
vector<int> edge[MAXN];

bool dead[MAXN];
void dfsSZ (int nd, int par) {
    sz[nd] = 1;
    for (auto id : edge[nd]) {
        int v = xr[id] ^ nd;
        if (v != par && !dead[v]) {
            dfsSZ(v, nd);
            sz[nd] += sz[v];
        }
    }
}

int FULL;
pii dfsCen (int nd, int par) {
    pii res = {nd, MOD};
    int mx = FULL - sz[nd];

    for (auto id : edge[nd]) {
        int v = xr[id] ^ nd;
        if (v != par && !dead[v]) {
            pii cur = dfsCen(v, nd);
            if (cur.Y < res.Y) {
                res = cur;
            }
            mx = max(mx, sz[v]);
        }
    }
//    debug(res.X, res.Y, mx, nd, sz[nd]);
    if (mx < res.Y) {
        res = {nd, mx};
    }
    return res;
}

int dis[MAXLG][MAXN];
int pp[MAXLG][MAXN];
int pa[MAXN];

int globCur[MAXN];
int cenCur[MAXN];
bool childCur[MAXLG][MAXN];

priority_queue<pii> globMX, cenMX[MAXN], childMX[MAXN];

void buildChild (int nd, int par, int root, int lev) {
    childCur[lev][nd] = true;
    childMX[root].emplace(dis[lev][nd], nd);

    pp[lev][nd] = root;
    for (auto id : edge[nd]) {
        int v = xr[id] ^ nd;
        if (v != par && !dead[v]) {
            buildChild(v, nd, root, lev);
        }
    }
}

void buildDis (int nd, int par, int d, int lev) {
    dis[lev][nd] = d;
    for (auto id : edge[nd]) {
        int v = xr[id] ^ nd;
        if (v != par && !dead[v]) {
            buildDis(v, nd, d+w[id], lev);
        }
    }
}

void updChild (int eid, int lev, int cen) {
    pa[eid] = cen;
    while (childMX[eid].size()) {
        const pii &tp = childMX[eid].top();
        if (!childCur[lev][tp.Y]) {
            childMX[eid].pop();
        } else {
            break;
        }
    }
    /* TODO not push when equal*/
    if (childMX[eid].empty()) {
        cenCur[eid] = -MOD;
    } else {
        cenCur[eid] = childMX[eid].top().first;
    }
    debug("insert", cenCur[eid], eid, cen);
    cenMX[cen].emplace(cenCur[eid], eid);
}

int lvv[MAXN];

bool on[MAXN];
void updCen (int nd) { // nd is centroid
    int lev = lvv[nd];
    while (cenMX[nd].size()) {
        const pii &tp = cenMX[nd].top();
        debug(tp.X, tp.Y, cenCur[tp.Y]);
        if (cenCur[tp.Y] != tp.X) {
            cenMX[nd].pop();
        } else {
            break;
        }
    }
    int fs = -MOD, sc = -MOD;
    if (on[nd]) {
        sc = 0;
        fs = 0;
    }
    if (cenMX[nd].empty()) {
        globCur[nd] = fs;
        globMX.emplace(globCur[nd], nd);
    } else {
        debug("has child", nd);

        pii tmp = cenMX[nd].top();
        fs = tmp.X;
        debug(tmp.X, tmp.Y);

        while (cenMX[nd].size()) {
            const pii &tp = cenMX[nd].top();
            if (cenCur[tp.Y] != tp.X || tp.Y == tmp.Y) {
                cenMX[nd].pop();
            } else {
                break;
            }
        }

        if (cenMX[nd].size()) {
            pii tt = cenMX[nd].top();
            sc = max(sc, cenMX[nd].top().X);
        }
        cenMX[nd].emplace(tmp);

        globCur[nd] = max(0, fs + sc);
        globMX.emplace(globCur[nd], nd);
    }

    debug(nd, globCur[nd], fs, sc);
}

void CentroidDecomp (int root, int lev) {
    dfsSZ(root, -1);
    FULL = sz[root];
//    pary(sz+1, sz+1+n);
//    debug(FULL);
    int cen = dfsCen(root, -1).X;
    lvv[cen] = lev;

    buildDis(cen, cen, 0, lev);
    dead[cen] = true;
    debug(cen, lev);
    for (auto id : edge[cen]) {
        int v = xr[id] ^ cen;
        if (!dead[v]) {
            buildChild(v, cen, id, lev);
            updChild(id, lev, cen);

            CentroidDecomp(v, lev+1);
        }
    }
    updCen(cen);
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    for (int i=0; i<n-1; i++) {
        int u, v;

        #ifdef tmdd
        u = i + 2;
        v = rand() % (i+1) + 1;
        w[i] = rand() % 10 - 5;
        #else
        cin >> u >> v >> w[i];
        #endif // tmd
        xr[i] = u ^ v;
        edge[u].eb(i);
        edge[v].eb(i);
    }

    fill(on, on+n+1, 1);
    memset(pp, -1, sizeof(pp));
    CentroidDecomp(1, 0);

    int q;
    cin >> q;

    int cnt = n;

    while (q--) {
        char cmd;
        #ifdef tmdd
        cmd = rand() % 10 == 0 ? 'A' : 'C';
        #else
        cin >> cmd;
        #endif // tmd

        if (cmd == 'A') {
            if (cnt == 0) {
                cout << "They have disappeared." << endl;
            } else {
                while (globMX.size()) {
                    const pii &tp = globMX.top();
                    debug(tp.X, tp.Y);
                    if (globCur[tp.Y] != tp.X) {
                        globMX.pop();
                    } else {
                        break;
                    }
                }

//                debug(globCur[3]);
                while(globMX.size() == 0){

                }
                cout << globMX.top().first << endl;
            }

        } else {
            int nd;
            #ifdef tmdd
            nd = rand() % n + 1;
            #else
            cin >> nd;
            #endif // tmd

            debug(cmd, nd, on[nd]);

            if (on[nd]) {
                on[nd] ^= 1;

                for (int i=0; i<MAXLG; i++) {
                    if (pp[i][nd] == -1) {
                        break;
                    }
                    childCur[i][nd] = false;

                    int cen = pa[pp[i][nd]];
                    /* BUGGGG */
                    updChild(pp[i][nd], i, cen);
                    updCen(cen);
                }
                updCen(nd);

                cnt--;
            } else {
                on[nd] ^= 1;

                for (int i=0; i<MAXLG; i++) {
                    debug(nd, pp[i][nd]);
                    if (pp[i][nd] == -1) {
                        break;
                    }
                    int ch = pp[i][nd];
                    childCur[i][nd] = true;
                    childMX[ch].emplace(dis[i][nd], nd);

                    int cen = pa[ch];
                    debug(cen);
                    updChild(ch, i, cen);
                    updCen(cen);
                }

                updCen(nd);
                cnt++;
            }
        }
    }

}
/*
10
2 1 7
3 1 5
4 3 -4
5 1 -8
6 5 -5
7 2 10
8 3 -10
9 5 3
10 3 4
10
C 7
C 7
A

*/
