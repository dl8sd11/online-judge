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

const int MAXN = 10005;
const ll MOD = 1000000007;

int n, w[MAXN];

int seg[MAXN*2];

void build () {
    for (int i=n-1; i>0; i--) {
        seg[i] = max(seg[i<<1], seg[i<<1|1]);
    }
}

int segQ (int l, int r) {
    int ret = 0;
    for (l+=n,r+=n; l<r; l>>=1, r>>=1) {
        if (l&1) {
            ret = max(ret, seg[l++]);
        }
        if (r&1) {
            ret = max(ret, seg[--r]);
        }
    }
    return ret;
}

void segM (int x, int v) {
    for (seg[x+=n]=v; x>1; x>>=1) {
        seg[x>>1] = max(seg[x], seg[x^1]);
    }
}

pii edge[MAXN];
vector<int> G[MAXN];

int sz[MAXN], dep[MAXN], in[MAXN], out[MAXN], head[MAXN], p[MAXN];
void dfsSZ (int nd, int par) {
    sz[nd] = 1;
    p[nd] = par;
    dep[nd] = dep[par] + 1;
    for (auto &v : G[nd]) {
        if (v != par) {
            dfsSZ(v, nd);
            sz[nd] += sz[v];

            if (G[nd][0]==par||sz[v] > sz[G[nd][0]]) {
                swap(v, G[nd][0]);
            }
        }
    }
}

int ts;
void dfsHD (int nd, int par) {
    in[nd] = ts++;
    for (auto v : G[nd]) {
        if (v != par) {
            if (v == G[nd][0]) {
                head[v] = head[nd];
            } else {
                head[v] = v;
            }
            debug(v, nd, par, G[nd][0]);
            dfsHD(v, nd);
        }
    }
    out[nd] = ts;
}

int pathQ (int u, int v) {
    int res = 0;
    while (head[u] != head[v]) {
        debug(u, v, head[u], head[v]);
        if (dep[head[u]] < dep[head[v]]) {
            swap(u, v);
        }
        res = max(res, segQ(in[head[u]], in[u]+1));
        u = p[head[u]];
    }
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    return max(res, segQ(in[v]+1, in[u]+1));
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    int t;
    cin >> t;

    while (t--) {
        cin >> n;
        for (int i=0; i<n-1; ++i) {
            int u, v;
            cin >> u >> v >> w[i];
            G[u].eb(v);
            G[v].eb(u);
            edge[i] = {u, v};
        }

        dfsSZ(1,0);

        head[1] = 1;
        ts = 0;
        dfsHD(1,0);

        pary(head+1, head+1+n);
        pary(sz+1, sz+1+n);

        for (auto &p : edge) {
            if (dep[p.X] < dep[p.Y]) {
                swap(p.X, p.Y);
            }
        }

        for (int i=0; i<n-1; i++) {
            seg[in[edge[i].X]+n] = w[i];
        }
        build();

        string cmd;
        while (cin >> cmd) {
            if (cmd[0] == 'D') {
                break;
            } else if (cmd[0] == 'Q') {
                int u, v;
                cin >> u >> v;
                cout << pathQ(u, v) << endl;
            } else {
                int id, x;
                cin >> id >> x;
                segM(in[edge[id-1].X], x);
            }
        }


        for (int i=1; i<=n; i++) {
            G[i].clear();
        }
    }
}
/*
1
5
1 2 2
2 3 3
2 4 4
1 5 1
QUERY 3 4
*/
