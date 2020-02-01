#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define eb emplace_back
#define MEM(a,b) memset(a,(b),sizeof(a))
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
template<typename IT> ostream&  __printRng(ostream &os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg;it!=ed;it++) {
        cout << (it==bg?"":",") << *it;
    }
    os << "}";
    return os;
}
template<typename T> ostream& operator << (ostream &os, vector<T> &vec) {
    return __printRng(os, vec.begin(), vec.end());
}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 10004;

int n, m;
int d[MAXN];
vector<int> fwd[MAXN], bwd[MAXN];
int csum[MAXN], mx[MAXN], deg[MAXN];

bool ct[MAXN];
/*********Good***Luck*********/
int main () {
    IOS();

    cin >> n;
    cin >> m;
    REP1 (i,n) {
        cin >> d[i];
    }
    REP (i,m) {
        int f, t;
        cin >> f >> t;
        fwd[f].emplace_back(t);
        bwd[t].emplace_back(f);
        deg[t]++;
    }

    vector<int> topo;
    queue<int> bfs;
    REP1 (i, n) {
        if (SZ(bwd[i]) == 0) {
            bfs.emplace(i);
        }
    }
    while (bfs.size()) {
        int cur = bfs.front();
        bfs.pop();
        topo.emplace_back(cur);

        for (auto x : fwd[cur]) {
            deg[x]--;
            if (deg[x] == 0) {
                bfs.emplace(x);
            }
        }
    }
    debug(topo);

    for (auto f : topo) {
        mx[f] += d[f];
        csum[f]++;
        for (auto t : fwd[f]) {
            if (mx[t] < mx[f]) {
                mx[t] = mx[f];
                csum[t] = csum[f];
            } else if (mx[t] == mx[f]) {
                csum[t] += csum[f];
            }
        }
    }

    int ans = 0;
    int res = 0;
    REP1 (i, n) {
        if (fwd[i].empty()) {
            res = max(res, mx[i]);
        }
    }


    reverse(ALL(topo));
    for (auto v : topo) {
        if (mx[v] == res) {
            ct[v] = true;
        }
        if (ct[v]) {
            for (auto t : bwd[v]) {
                if (mx[t] == mx[v] - d[v]) {
                    ct[t] = true;
                }
            }
        }
    }

    REP1 (i, n) {
        ans += ct[i];
    }
    debug(ans, res);

    cout << ans << endl;
    return 0;
}
