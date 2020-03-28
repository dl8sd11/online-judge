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

const int MAXN = 40004;
const int MAXLG = __lg(MAXN) + 2;
const ll MOD = 1000000007;

int n, m, w[MAXN];
vector<int> edge[MAXN];

int in[MAXN], out[MAXN], ck, anc[MAXLG][MAXN], dep[MAXN];

void dfs (int nd, int par) {
    in[nd] = ck++;
    anc[0][nd] = par;
    dep[nd] = dep[par] + 1;

    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
        }
    }

    out[nd] = ck++;
}

void build_anc () {
    for (int i=1; i<MAXLG; i++) {
        for (int j=1; j<=n; j++) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int lca (int u, int v) {
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    for (int i=MAXLG-1; i>=0; i--) {
        if (dep[anc[i][v]] >= dep[u]) {
            v = anc[i][v];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i=MAXLG-1; i>=0; i--) {
        if (anc[i][v] != anc[i][u]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }
    return anc[0][u];
}


const int K = 250;
struct Query {
    int l, r, qid, lid, x, y;
    Query (int u, int v, int q) : qid(q) {
        if (in[u] > in[v]) {
            swap(u, v);
        }
        l = in[u] + 1;
        r = in[v];
        lid = l / K;
        x = u;
        y = v;
    }

    bool operator < (const Query &oth) const {
        if (lid != oth.lid) {
            return lid < oth.lid;
        } else {
            if (lid & 1) {
                return r > oth.r;
            } else {
                return r < oth.r;
            }
        }
    }
};
vector<Query> query;
bool state[MAXN*2];
int seq[MAXN*2];
int cnt[MAXN], curAns;

void add (int x) {
    cnt[x]++;
    if (cnt[x] == 1) {
        curAns++;
    }
}

void sub (int x) {
    cnt[x]--;
    if (cnt[x] == 0) {
        curAns--;
    }
}

void tog (int id) {
//    debug(id, seq[id], state[id]);
    if (state[seq[id]]) {
        sub(w[seq[id]]);
    } else {
        add(w[seq[id]]);
    }
    state[seq[id]] ^= 1;
}

int ans[100005];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    vector<int> val;
    REP1 (i,n) {
        cin >> w[i];
        val.eb(w[i]);
    }

    sort(ALL(val));
    val.resize(unique(ALL(val))-val.begin());
    REP1 (i, n) {
        w[i] = lower_bound(ALL(val), w[i])-val.begin();
    }

    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs(1, 0);
    build_anc();

    for (int i=1; i<=n; i++) {
        seq[in[i]] = i;
        seq[out[i]] = i;
    }

    query.reserve(m);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        query.eb(u, v, i);
    }

    sort(ALL(query));
    int L = 0, R = -1;
    for (const Query &q : query) {
        if (q.x == q.y) {
            ans[q.qid] = 1;
            continue;
        }
        while (L > q.l) {
            tog(--L);
        }
        while (R < q.r) {
            tog(++R);
        }
        while (L < q.l) {
            tog(L++);
        }
        while (R > q.r) {
            tog(R--);
        }

        int ca = lca(q.x, q.y);
        tog(in[ca]);
        debug(q.l, q.r, q.qid, in[ca]);
        ans[q.qid] = curAns;
        tog(in[ca]);
    }

    REP (i, m) {
        cout << ans[i] << endl;
    }
}
/*
6 6
7 9 3 2 9 4
1 2
2 3
1 4
4 5
4 6
1 1
2 2
3 3
4 4
5 5
6 6

*/
