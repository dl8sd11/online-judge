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
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> ostream &operator << (ostream &os,multiset<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const int MAXLG = __lg(MAXN) + 1;
const ll MOD = 1000000007;

int n, q;
ll w, len[MAXN];
int xr[MAXN];
vector<int> eid[MAXN];
set<pair<ll,int> > dp[MAXN];
ll bst[MAXN];
multiset<pair<ll,int> > ans;
int h;

struct ZKWTree {
    int sz;
    vector<ll> t, d;

    ZKWTree (int _n) : sz(_n), t(sz*2), d(sz*2){}

    void init () {
        for (int i=sz-1; i>0; i--) {
            t[i] = max(t[i<<1], t[i<<1|1]);
        }
    }

    ll get () {
        return t[1];
    }

    void apply(int p, ll value) {
      t[p] += value;
      if (p < n) d[p] += value;
    }

    void build(int p) {
      while (p > 1) p >>= 1, t[p] = max(t[p<<1], t[p<<1|1]) + d[p];
    }

    void inc(int l, int r, ll value) {
      l += sz, r += sz;
      int l0 = l, r0 = r;
      for (; l < r; l >>= 1, r >>= 1) {
        if (l&1) apply(l++, value);
        if (r&1) apply(--r, value);
      }
      build(l0);
      build(r0 - 1);
    }

};
vector<ZKWTree> seg;

struct CentroidData {
    int anc;
    int subL, subR;
    int segID;
};
CentroidData cent[MAXLG][MAXN];
int csz[MAXN];

bool dead[MAXN];
void build_cen_sub (int nd, int par, int segID, int root, ll dis, ll &far, int &tms) {
    int st = tms++;
    far = max(far, dis);

    seg[segID].t[seg[segID].sz+st] = dis;
    for (auto id : eid[nd]) {
        int v = xr[id] ^ nd;
        if (!dead[v] && v != par) {
            int bg = tms;
            build_cen_sub(v, nd, segID, root, dis+len[id], far, tms);

            cent[csz[id]++][id] = {root, bg, tms, segID};
        }
    }
}

void update (int nd) {
    ans.erase({bst[nd],nd});
    ll d = 0;
    if (dp[nd].size() >= 2) {
        auto ptr = dp[nd].end();
        d += (--ptr)->first;
        d += (--ptr)->first;
    } else if (dp[nd].size() >= 1) {
        auto ptr = dp[nd].end();
        d += (--ptr)->first;
    }

    bst[nd] = d;
    ans.insert({bst[nd], nd});
}

int sz[MAXN], ssum;
void build_cen (int nd) {

    for (auto id : eid[nd]) {
        int v = xr[id] ^ nd;
        if (!dead[v]) {
            seg.emplace_back(sz[v]);
            ll far = 0;
            int tms = 0;
            build_cen_sub(v,nd,SZ(seg)-1,nd,len[id],far,tms);
            cent[csz[id]++][id] = {nd,0,tms,SZ(seg)-1};

            dp[nd].insert({far, SZ(seg)-1});
        }
    }

    ans.insert({0, nd});
    update(nd);

}


void dfs_sz (int nd, int par) {
    sz[nd] = 1;
    for (auto id : eid[nd]) {
        int v = xr[id] ^ nd;
        if (v != par && !dead[v]) {
            dfs_sz(v, nd);
            sz[nd] += sz[v];
        }
    }
}

pair<int,int> dfs_cen (int nd, int par, int hd) {
    int mx = hd;
    pair<int,int> mn = {-1, MOD};

    for (auto id : eid[nd]) {
        int v = xr[id] ^ nd;
        if (v == par || dead[v]) {
            continue;
        }
        pair<int,int> cur = dfs_cen(v,nd,ssum-sz[v]);
        if (cur.Y < mn.Y) {
            mn = cur;
        }
        mx = max(mx, sz[v]);
    }
    if (mx < mn.Y) {
        mn = {nd, mx};
    }
    return mn;
}

void CentroidDecomp (int root) {
    dfs_sz(root, -1);
    ssum = sz[root];
    int cen = dfs_cen(root, -1, 0).X;

    build_cen(cen);

    dead[cen] = true;
    for (auto id : eid[cen]) {
        int v = xr[id] ^ cen;
        if (!dead[v]) {
            CentroidDecomp(v);
        }
    }
}


// warn: take care for leaf
void change (int id, ll nw) {
    ll dl = nw - len[id];
    REP (i, csz[id]) {
        auto &cen = cent[i][id];

        assert(cen.segID < SZ(seg));
        ll dis = seg[cen.segID].get();
        dp[cen.anc].erase({dis, cen.segID});

        seg[cen.segID].inc(cen.subL,cen.subR,dl);

        dis = seg[cen.segID].get();
        dp[cen.anc].insert({dis, cen.segID});

        update(cen.anc);
    }
    len[id] = nw;
}

ll dia () {
    return prev(ans.end())->first;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q >> w;
    h = sizeof(int) * 8 - __builtin_clz(n);

    REP (i, n-1) {
        int u, v, c;
        cin >> u >> v >> c;
        len[i] = c;
        xr[i] = u ^ v;
        eid[u].eb(i);
        eid[v].eb(i);
    }

    CentroidDecomp(1);
    for (auto &dseg : seg) {
        dseg.init();
    }

    ll last = 0;
    while (q--) {
        ll d, e;
        cin >> d >> e;
        d = (d + last) % (n-1);
        e = (e + last) % w;

        change(d, e);

        last = dia();
        cout << last << endl;
    }
}
/*
TLE: compare to https://codeforces.com/contest/1192/submission/57780920
*/
