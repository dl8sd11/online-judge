#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("03","unroll-loops")
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define MEM(a,b) memset(a,(b),sizeof(a))
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d: (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
template<typename T> ostream &operator << (ostream &os, const pair<T,T> &p){return os<<"("<<p.first<<","<<p.second<<")";}
template<typename IT> ostream &_printRng(ostream &os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        os << (it==bg?"":",") << *it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os, const vector<T> &vec) {return _printRng(os, vec.begin(),vec.end());}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 100005;

int n, m;

struct Edge {
    int u, v, w;
    bool operator < (const Edge &edg) const {
        return w > edg.w;
    }
};
vector<Edge> edge;

int djs[MAXN], sz[MAXN];
void init () {
    REP1 (i, n) {
        djs[i] = i;
        sz[i] = 1;
    }
}

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

bool uni (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x == y) {
        return false;
    }
    if (sz[x] > sz[y]) {
        swap(x, y);
    }
    djs[x] = y;
    return true;
}
int main () {
    IOS();

    cin >> n >> m;
    edge.resize(m);
    int ans = 0;
    REP (i, m) {
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
        ans += edge[i].w;
    }

    sort(edge.begin(), edge.end());

    init();
    for (const Edge &e : edge) {
        if (uni(e.u, e.v)) {
            ans -= e.w;
        }
    }

    cout << ans << endl;

}
