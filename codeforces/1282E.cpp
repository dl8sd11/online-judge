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
const ll MOD = 1000000007;

int t, n;
vector<int> edge[MAXN];
map<array<int,2>, int> edge_cnt;
map<array<int,3>, int > tri_id;
set<array<int,3> > tri[MAXN];

vector<int> p, q;

bool vis[MAXN];
void dfs_p (int nd) {
    vis[nd] = true;
    p.eb(nd);

    for (auto v : edge[nd]) {
        if (!vis[v]) {
            dfs_p(v);
        }
    }
}

void build_p () {
    for (auto pe : edge_cnt) {
        if (pe.second == 1) {
            edge[pe.first[0]].eb(pe.first[1]);
            edge[pe.first[1]].eb(pe.first[0]);
        }
    }

    memset(vis, 0, sizeof(bool)*(n+1));
    dfs_p(1);
}

void build_q () {
    set<array<int,3> > bfs;
    REP1 (i, n) {
        if (SZ(tri[i]) == 1) {
            bfs.emplace(*tri[i].begin());
        }
    }

    while (bfs.size()) {
        auto cur = *bfs.begin();
        bfs.erase(bfs.begin());

        q.eb(tri_id[cur]);

        for (int i : cur) {
            tri[i].erase(cur);
            if (tri[i].size() == 1) {
                bfs.insert(*tri[i].begin());
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n;

        REP (i, n-2) {
            array<int,3> cur;
            REP (j, 3) {
                cin >> cur[j];
            }
            sort(ALL(cur));
            tri_id[cur] = i + 1;

            REP (j, 3) {
                tri[cur[j]].insert(cur);
                array<int,2> ce = {cur[j], cur[(j+1)%3]};
                sort(ALL(ce));
                edge_cnt[ce]++;
            }
        }

        build_p();
        build_q();

        debug(p);
        debug(q);

        assert(SZ(p) == n);
        assert(SZ(q) == n-2);

        REP (i, n) {
            cout << p[i] << " \n"[i==n-1];
        }
        REP (i, n-2) {
            cout << q[i] << " \n"[i==n-3];
        }

        p.clear();
        q.clear();
        tri_id.clear();
        REP1 (i, n) {
            edge[i].clear();
            assert(tri[i].empty());
        }
        edge_cnt.clear();
    }
}
