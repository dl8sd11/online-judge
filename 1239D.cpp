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

const int MAXN = 1000006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int T, n, m;
vector<int> edge[MAXN], redge[MAXN];

bool vis[MAXN];
vector<int> topo;
vector<int> jury, cats;

void build_topo (int nd) {
    vis[nd] = true;
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            build_topo(v);
        }
    }
    topo.emplace_back(nd);
}


void build_scc (int nd, int cnt) {
    vis[nd] = false;
    if (cnt == 0) {
        cats.emplace_back(nd);
    } else {
        jury.emplace_back(nd);
    }
    for (auto v : redge[nd]) {
        if (vis[v]) {
            build_scc(v, cnt);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> T;
    while (T--) {
        cin >> n >> m;

        REP (i, m) {
            int f, t;
            cin >> f >> t;
            if (f != t) {
                edge[f].emplace_back(t);
                redge[t].emplace_back(f);
            }
        }

        topo.clear();
        REP1 (i, n) {
            if (!vis[i]) {
                build_topo(i);
            }
        }
        reverse(topo.begin(), topo.end());

        int cnt = 0;
        jury.clear(), cats.clear();
        for (auto v : topo) {
            if (vis[v]) {
                build_scc(v, cnt++);
            }
        }

        if (jury.empty() || cats.empty()) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
            cout << SZ(jury) << " " << SZ(cats) << endl;
            REP (i, SZ(jury)) {
                cout << jury[i] << " \n"[i==SZ(jury)-1];
            }
            REP (i, SZ(cats)) {
                cout << cats[i] << " \n"[i==SZ(cats)-1];
            }
        }

        REP1 (i, n) {
            edge[i].clear();
            redge[i].clear();
        }
    }
}
