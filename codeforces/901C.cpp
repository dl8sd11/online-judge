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

const int MAXN = 300005;
const ll MOD = 1000000007;

int n, m;
vector<int> edge[MAXN];

int pa[MAXN];
bool vis[MAXN];

vector<vector<int> > cs;

void buildCycle (int nd, int goal) {
    vector<int> cur;
    do {
        cur.emplace_back(nd);
        nd = pa[nd];
    } while (nd != goal);
    cur.eb(goal);

    cs.eb(cur);
    debug(cur, nd, goal);
}

int dep[MAXN];
void dfs (int nd, int par) {
    vis[nd] = true;
    pa[nd] = par;
    dep[nd] = dep[par] + 1;

    for (auto v : edge[nd]) {
        if (v != par) {
            if (!vis[v]) {
                dfs(v, nd);
            } else if (dep[v] < dep[nd]) {
                debug(nd, v, par);
                buildCycle(nd, v);
            }
        }
    }
}

ll seg[MAXN*2];

void build () {
    for (int i=n-1; i>0; i--) {
        seg[i] = seg[i<<1] + seg[i<<1|1];
    }
}

ll qry (int l, int r) {
    ll ret = 0;
    for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
        if (l&1) {
            ret += seg[l++];
        }
        if (r&1) {
            ret += seg[--r];
        }
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        u--,v--;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    for (int i=0; i<n; i++) {
        if (!vis[i]) {
            dfs(i, i);
        }
    }

    vector<pii> pos;
    for (auto c : cs) {
        sort(ALL(c));
        pos.emplace_back(c.front(), c.back());
    }


    sort(ALL(pos));
    debug(pos);
    vector<pii> stk = {{-1,-1}};
    for (auto v : pos) {
        while (stk.size() && stk.back().Y >= v.Y) {
            stk.pop_back();
        }

        if (stk.size() && stk.back().X == v.X) {
            continue;
        }

        stk.eb(v);
    }
    stk.eb(n,n);
    debug(stk);

    for (int i=1; i<stk.size(); i++) {
        for (int j=stk[i-1].X+1; j<=stk[i].X; j++) {
            seg[j+n] = stk[i].Y - 1;
        }
    }

    build();

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--,r--;
        int L = l-1, R = n;
        while (L < R - 1) {
            int M = (L + R) >> 1;
            if (seg[M+n] <= r) {
                L = M;
            } else {
                R = M;
            }
        }

        ll len = (r - l + 1);
        ll sum = (len + 1) * len / 2;

        ll sub = (R-l);

        debug(seg[n]);
        debug(len, sum, sub, l, R, qry(l,R));
        sum -= sub * r - qry(l,R);
        cout << sum << endl;
    }
}
