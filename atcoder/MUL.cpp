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

const int MAXN = 102;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, a[MAXN], s, t;

struct Edge {
    int t;
    ll cap, flow;
    int nxt;
} edge[MAXN*21];

int ecnt, head[MAXN];
void add_edge (int F, int T, ll cap) {
    debug(F, T, cap);
    edge[ecnt] = {T, cap, 0, head[F]};
    head[F] = ecnt++;
    edge[ecnt] = {F, 0, 0, head[T]};
    head[T] = ecnt++;
}

int lev[MAXN], cur[MAXN];

ll dfs (int nd, ll lim) {
    if (nd == t || lim == 0) {
        return lim;
    }

    for (int &it=cur[nd];it!=-1;it=edge[it].nxt) {
        int x = edge[it].t;

        ll rem = edge[it].cap - edge[it].flow;
        if (lev[x] == lev[nd] + 1 && rem > 0) {
            int df = dfs(x, min(lim, rem));
            if (df > 0) {
                edge[it].flow += df;
                edge[it^1].flow -= df;
                return df;
            }
        }
    }

    return 0;
}

bool bfs () {
    memset(lev, -1, sizeof(lev));
    queue<int> que;
    que.emplace(s);
    lev[s] = 0;

    while (que.size()) {
        int nd = que.front();
        que.pop();

        for (int it=head[nd];it!=-1;it=edge[it].nxt) {
            int v = edge[it].t;

            if (lev[v] == -1 && edge[it].cap > edge[it].flow) {
                lev[v] = lev[nd] + 1;
                que.emplace(v);
            }
        }
    }

    return lev[t] != -1;
}

ll Dinic () {
    ll res = 0;
    while (bfs()) {
        ll df = 0;

        REP (i, MAXN) {
            cur[i] = head[i];
        }

        while (df = dfs(s, INF)) {
            res += df;
        }
    }

    return res;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    memset(head, -1, sizeof(head));

    s = 0, t = 101;
    cin >> n;

    ll ans = 0;
    REP1 (i, n) {
        cin >> a[i];
        if (a[i] > 0) {
            add_edge(i, t, a[i]);
            ans += a[i];
        } else {
            add_edge(s, i, -a[i]);
        }
    }

    REP1 (i, n) {
        for (int j=2; j*i<=n; j++) {
            add_edge(i, j*i, INF);
        }
    }

    ll flow = Dinic();
    debug(flow);
    cout << ans - flow << endl;
}
