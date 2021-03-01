#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define eb emplace_back
#define X first
#define Y second

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

struct QUERY {
    ll x,y,z;
};

struct SOLVER {
    vector<ll> qid;
    ll L,R;
};

ll n,m,q,ans[MAXN];
vector<pii> edge;
vector<QUERY> Q;
ll djs[MAXN],sz[MAXN];

void init() {
    REP (i,MAXN) {
        djs[i] = i;
        sz[i] = 1;
    }
}

ll fnd(ll x) {
    return djs[x] == x ? x : djs[x] = fnd(djs[x]);
}

void uni(ll x,ll y) {
    if (sz[x=fnd(x)] < sz[y=fnd(y)]) swap(x,y);
    djs[y] = x;
    sz[x] += sz[y];
}

/********** Good Luck :) **********/
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    edge.eb(-1,-1);
    REP (i,m) {
        ll u,v;
        cin >> u >> v;
        edge.eb(u,v);
    }

    cin >> q;
    REP (i,q) {
        ll x,y,z;
        cin >> x >> y >> z;
        Q.push_back({x,y,z});
    }

    vector<ll> qid;
    REP (i,q) {
        qid.eb(i);
    }

    queue<SOLVER> BFS;
    BFS.push({qid,0,m+1});

    
    ll state = INF;
    while (BFS.size()) {
        SOLVER cur = BFS.front();BFS.pop();
        if (cur.L == cur.R - 1) {
            for (auto v:cur.qid) {
                ans[v] = cur.L;
            }
            continue;
        }

        ll mid = (cur.L + cur.R) / 2;
        if (mid - 1 < state) {
            init();
            state = 0;
        }

        while (state < mid - 1) {
            state++;
            if (fnd(edge[state].X) != fnd(edge[state].Y)) {
                uni(edge[state].X,edge[state].Y);
            }
        }

        vector<ll> lV,rV;
        for (auto v:cur.qid) {
            ll siz = (fnd(Q[v].x) == fnd(Q[v].y) ? sz[fnd(Q[v].x)]:sz[fnd(Q[v].x)] + sz[fnd(Q[v].y)]);
            if (siz >= Q[v].z) {
                lV.eb(v);
            } else {
                rV.eb(v);
            }
        }

        BFS.push({lV,cur.L,mid});
        BFS.push({rV,mid,cur.R});
    }

    REP (i,q) {
        cout << ans[i] << endl;
    }
    
    return 0;
}
