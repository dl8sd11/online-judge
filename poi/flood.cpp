#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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

const int MAXN = 500005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, h;
struct Edge {
    int u, v, w;
    bool operator < (const Edge &edg) const {
        return w < edg.w;
    }
};
vector<Edge> edge;

int djs[MAXN], mx[MAXN], ans[MAXN];

void init () {
    REP (i, n*m) {
        djs[i] = i;
        mx[i] = 0;
        ans[i] = 1;
    }
}

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void mrg (int x, int y, int mid) {
    x = fnd(x), y = fnd(y);
    if (x == y) {
        return;
    }
    djs[x] = y;
    ans[y] = 1LL * (ans[x] + (mid-mx[x])) * (ans[y] + (mid-mx[y])) % MOD;
    mx[y] = mid;
}

int toID (int x, int y) {
    return x*m + y;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> h;
    REP (i, n) {
        REP (j, m-1) {
            int d;
            cin >> d;
            edge.push_back({toID(i,j),toID(i,j+1),d});
        }
    }
    REP (i,n-1) {
        REP (j,m) {
            int d;
            cin >> d;
            edge.push_back({toID(i,j),toID(i+1,j),d});
        }
    }
    sort(edge.begin(),edge.end());

    init();
    for (auto e : edge) {
        mrg(e.u, e.v, e.w);
        debug(e.u, e.v, ans[fnd(e.u)]);
    }

    cout << (ans[fnd(0)] + (h-mx[fnd(0)])) % MOD << endl;
}
