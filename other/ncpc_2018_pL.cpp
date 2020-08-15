#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
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

bool QTYPE=0;
struct Line {
    mutable int k, m, p;
    bool operator<(const Line& o) const { 
        if (QTYPE) return p<o.p;
        return k < o.k; 
    }
};

struct LineContainer : multiset<Line > {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    const int inf = LLONG_MAX;
    int div(int a, int b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return false; }
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(int k, int m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    int query(int x) {
        assert(!empty());
        QTYPE=1; auto l = *lower_bound({0,0,x}); QTYPE = 0;
        return l.k * x + l.m;
    }
};

vector<pii> edge[MAXN];
int w[MAXN], dep[MAXN], p[MAXN];

struct INFO {
    LineContainer hull[2]; 
    int child[2];
    int root;
    void dfs (int nd, int par, int id) {
        hull[id].add(w[nd], w[nd] * (dep[nd]-dep[root]));
        for (auto v : edge[nd]) {
            if (v.X != par) {
                dfs(v.X, nd, id);
            }
        }
    }
    void make (int nd) {
        root = nd;
        int itr = 0;
        for (auto v : edge[nd]) {
            if (v.X != p[nd]) {
                child[itr] = v.X;
                dfs(v.X, nd, itr);
                itr++;
            }
        }

    }
    void clear() {
        hull[0].clear();
        hull[1].clear();
    }
};

INFO info[MAXN];
LineContainer total, ntotal;
int ans[MAXN];
int in[MAXN], out[MAXN], tme;

vector<int> stk;

bool is_anc (int a, int b) {
    return in[a] <= in[b] && out[b] <= out[a];
}
void build_hull (int nd, int par) {
    ans[nd] = max(total.query(dep[nd]), ntotal.query(-dep[nd]));
    for (auto v : stk) {
        REP (i, 2) {
            if (is_anc(info[v].child[i], nd)) {
                continue;
            }
            ans[nd] = max(ans[nd], info[v].hull[i].query(dep[nd]-dep[v]));
        }

    }

    bool flag = false;
    if (SZ(edge[nd]) + (par == -1) == 3) {
        info[nd].make(nd);
        stk.eb(nd);
        flag = true;
    }
    for (auto v : edge[nd]) {
        if (v.X != par) {
            build_hull(v.X, nd);
        }
    }

    if (flag) {
        stk.pop_back();
    }
}

void build_dep (int nd, int par) {
    p[nd] = par;
    in[nd] = tme++;
    for (auto v : edge[nd]) {
        if (v.X != par) {
            dep[v.X] = dep[nd] + v.Y;
            build_dep(v.X, nd);
        }
    }
    out[nd] = tme++;
}
/*********************GoodLuck***********************/
signed main () {
    IOS();

    int t;
    cin >> t;
    while (t--) {
        tme = 0;
        int n;
        cin >> n;
        for (int i=0; i<n; i++) {
            cin >> w[i];
        }

        for (int i=0; i<n-1; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            u--, v--;
            edge[u].eb(v, c);
            edge[v].eb(u, c);
        }

        int root = 0;
        for (int i=0; i<n; i++) {
            if (SZ(edge[i]) == 1) {
                root = i;
            }
        }


        build_dep(root, -1);

        for (int i=0; i<n; i++) {
            total.add(w[i], -w[i]*dep[i]);
            ntotal.add(w[i], w[i]*dep[i]);
        }
        pary(dep, dep+n);
        
        debug(ntotal.query(0));
        build_hull(root, -1);


        pary(ans, ans+n);
        sort(ans, ans+n);
        cout << ans[(n-1)/2] << " " << ans[n-1] << endl;
        

        total.clear();
        ntotal.clear();
        for (int i=0; i<n; i++) {
            info[i].clear();
            edge[i].clear();
        }
    }


}

