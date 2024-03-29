#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
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
template<typename T> ostream &operator << (ostream &os,const vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, m, q;
vector<int> edge[MAXN];


struct Comp {
    pii dia;
    int len;
    ll sum;
    vector<int> vert;
    vector<int> dsrt;
    vector<ll> psum;
};
vector<Comp> comp;

int dis[MAXN];
bool vis[MAXN];
int ccid[MAXN], ccnt;

void buildComp (int nd, Comp &res) {
    vis[nd] = true;
    res.vert.eb(nd);
    ccid[nd] = ccnt;
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            buildComp(v, res);
        }
    }
}

pii far (int nd, int par) {
    pii res = {0, nd};
    for (auto v : edge[nd]) {
        if (v != par) {
            pii cur = far(v, nd);
            cur.X++;
            res = max(res, cur);
        }
    }
    return res;
}

void buildDis (int nd, int par, int d) {
    dis[nd] = max(dis[nd] , d);
    for (auto v : edge[nd]) {
        if (v != par) {
            buildDis(v, nd, d+1);
        }
    }
}

double solve (const Comp &sm, const Comp &bg) {
    ll bs = 0;
    bs += sm.sum * ll(bg.vert.size());
    bs += bg.sum * ll(sm.vert.size());
    ll sz = ll(bg.vert.size()) * ll(sm.vert.size());
    bs += sz;

//    debug(bs, sm.sum, bg.sum);
//    debug(sm.dsrt);
//    debug(bg.dsrt);

    int lm = max(sm.len, bg.len);
//    debug(bs, lm);
//    int edg = SZ(bg.dsrt);
    for (auto d : sm.dsrt) {
//        if ()
//        int L = 0, R = edg;


        int idx = lower_bound(ALL(bg.dsrt), lm-d-1) - bg.dsrt.begin();

        if (idx) {
            ll sub = idx + ll(d) * idx;
            sub += bg.psum[idx-1];
//            debug(sub, lm, d);
            bs -= sub;
            bs += ll(idx) * lm;
        }
    }

    debug(bs);
    return double(bs) / sz;
}

#ifdef tmd

double bf (const Comp &sm, const Comp &bg) {
    ll sum = 0;

    int mx = max(sm.len, bg.len);
    ll sz = 0;
    for (auto d1 : sm.dsrt) {
        for (auto d2 : bg.dsrt) {
            sum += max(d1+d2+1, mx);
            sz++;
        }
    }

    return double(sum) / sz;
}

int djs[MAXN];
int fnd(int nd) {
    return djs[nd] == nd ? nd : djs[nd] = fnd(djs[nd]);
}

void mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    djs[x] = y;
}
#endif // tmd

map<pii,double> ans;

/*********************GoodLuck***********************/
signed main () {
    IOS();
    srand(80);

    cin >> n >> m >> q;

    #ifdef tmdd
    for (int i=1; i<=n; i++) {
        djs[i] = i;
    }
    #endif
    for (int i=0; i<m; i++) {
        int u, v;
        #ifdef tmdd
        while (true) {
            u = rand() % n  + 1;
            v = rand() % n  + 1;
            if (fnd(u) != fnd(v)) {
                debug(u, v);
                mrg(u, v);
                break;
            }
        }
        #else
        cin >> u >> v;
        #endif // tmd
        edge[u].eb(v);
        edge[v].eb(u);
    }

    for (int i=1; i<=n; i++) {
        if (!vis[i]) {
            Comp cur;
            buildComp(i, cur);
            comp.eb(cur);
            debug(cur.vert);
            ccnt++;
        }
    }

    for (auto &cp : comp) {
        int root = cp.vert.front();
        int p1 = far(root, -1).Y;
        int p2 = far(p1, -1).Y;
        cp.dia = {p1, p2};

        buildDis(p1, -1, 0);
        buildDis(p2, -1, 0);
        cp.len = dis[p1];

        cp.sum = 0;
        for (auto v : cp.vert) {
            cp.sum += dis[v];
            cp.dsrt.eb(dis[v]);
        }

        sort(ALL(cp.dsrt));

        ll ac = 0;
        for (auto d : cp.dsrt) {
            ac += d;
            cp.psum.eb(ac);
        }
    }
    pary(dis+1, dis+1+n);
    debug("built");

    cout << fixed << setprecision(10);
    while (q--) {
        int u, v;
        #ifdef tmdd
        u = rand() % n + 1;
        v = rand() % n + 1;
        #else
        cin >> u >> v;
        #endif // tmd
        debug(u, v);
        if (ccid[u] != ccid[v]) {
            int uid = ccid[u];
            int vid = ccid[v];

            pii pa = {uid, vid};
            if (uid < vid) {
                swap(uid, vid);
            }
            if (ans.count(pa)) {
                debug("test");
                cout << ans[pa] << endl;
            } else {
                if (comp[uid].vert.size() > comp[vid].vert.size()) {
                    swap(uid, vid);
                }



                double res = solve(comp[uid], comp[vid]);
                cout << res << endl;

                ans[pa] = res;
            }


            #ifdef tmd
            double rl = bf(comp[uid], comp[vid]);
//            debug(res, rl);
//            assert(res == rl);
            #endif // tmd



        } else {
            cout << -1 << endl;
        }
    }
}
/*
10 8 1
1 2
2 3
3 4
4 5
5 6
6 7
8 9
9 10
1 8
*/
