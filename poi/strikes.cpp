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

const int MAXN = 500005;
const ll MOD = 1000000007;

int n, q;
vector<int> edge[MAXN];

struct Counter {
    int chOn[MAXN], par[MAXN];
    bool on[MAXN];

    void set (int nd, bool state) {
        on[nd] = state;
        chOn[par[nd]] += (state ? 1 : -1);
    }

    int qryOn (int nd) {
        return chOn[nd] + on[par[nd]];
    }

    int qryOff (int nd) {
        return SZ(edge[nd]) - qryOn(nd);
    }

    void dfs (int nd, int p) {
        par[nd] = p;
        for (int v : edge[nd]) {
            if (v != p) {
                dfs(v, nd);
            }
        }
    }

    Counter () {
        memset(chOn, 0, sizeof(chOn));
        memset(on, 0, sizeof(on));
        dfs(1, 0);
    }
};
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }
    
    Counter cnt;
    cin >> q;

    int comp = 1;
    while (q--) {
        int d;
        cin >> d;

        if (d > 0) {
            comp += cnt.qryOff(abs(d)) - 1;
        } else {
            comp -= cnt.qryOff(abs(d)) - 1;
        }
        cnt.set(abs(d), d>0);

        cout << comp << endl;
    }
}

