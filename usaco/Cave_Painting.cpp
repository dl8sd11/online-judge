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
template<typename T> ostream &operator << (ostream &os,set<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1003;
const ll MOD = 1000000007;

int n, m;
bool grid[MAXN][MAXN];
int nid[MAXN][MAXN];

int djs[MAXN*MAXN];

int fnd (int x) {
    return djs[x] == x ? x : djs[x] = fnd(djs[x]);
}

void mrg (int x, int y) {
    x = fnd(x);
    y = fnd(y);
    djs[x] = y;
}

int id (int x, int y) {
    return x * m + y;
}

set<int> edge[MAXN*MAXN];
int ind[MAXN*MAXN];

int nnode;

set<int> vis;
ll dfs (int nd) {
//    debug(nd);
    assert(vis.count(nd) == 0);
    vis.insert(nd);
    ll ret = 1;
    for (auto v : edge[nd]) {
        ll res = dfs(v);
        ret = ret * res % MOD;
    }

    return (ret + 1) % MOD;
}
/*********************GoodLuck***********************/
int main () {
//    IOS();
//srand(time(0));

    #ifndef tmd

    freopen("cave.in", "r", stdin);
    freopen("cave.out", "w", stdout);

    #endif // tmd

    cin >> n >> m;
    REP (i, n) {
        REP (j, m) {
            char c;
            #ifdef tmd
            c = rand() % 5 == 0 ? '#' : '.';
            if (i == 0 || i == n-1 || j == 0 || j == m-1) {
                c = '#';
            }
            #else
            cin >> c;
            #endif // tmd
            grid[i][j] = c == '.';
            djs[id(i,j)] = id(i,j);
        }
    }

    for (int i=n-2; i>=1; i--) {
        for (int j=1; j<m-1; j++) {
            if (grid[i][j]) {
                if (grid[i+1][j]) {
                    mrg(id(i,j), id(i+1,j));
                }
                if (grid[i][j-1]) {
                    mrg(id(i,j), id(i,j-1));
                }
            }
        }


        map<int,int> nmp;
        for (int j=1; j<m-1; j++) {
            if (grid[i][j]) {
                if (nmp.count(fnd(id(i,j))) == 0) {
                    nid[i][j] = ++nnode;
                    nmp[fnd(id(i,j))] = nnode;

                    if (grid[i+1][j]) {
                        assert(nid[i][j] > nid[i+1][j]);
                        assert(nid[i+1][j] >= 1);
                        edge[nid[i][j]].insert(nid[i+1][j]);
                        ind[nid[i+1][j]]++;
                    }
                } else {
                    nid[i][j] = nmp[fnd(id(i,j))];
                    if (grid[i+1][j]) {
                        assert(nid[i][j] > nid[i+1][j]);
                        assert(nid[i+1][j] >= 1);
                        edge[nid[i][j]].insert(nid[i+1][j]);
                        ind[nid[i+1][j]]++;
                    }
                }
            } else {
                nid[i][j] = -1;
            }
        }

    }

    #ifdef tmd
    REP (i, n) {
        pary(nid[i], nid[i]+m);
    }
    #endif // tmd

//    pary(ind+1, ind+nnode+1);
    ll ans = 1;
    REP1 (i, nnode) {
//        debug(i, edge[i]);
//        debug(i);
        if (ind[i] == 0) {
            vis.clear();
            ans = ans * dfs(i) % MOD;
        }
    }

    cout << ans << endl;

}

/*
6 13
#############
#...........#
#..#..#.....#
#...##...#..#
#..#..#..#..#
#############

*/
