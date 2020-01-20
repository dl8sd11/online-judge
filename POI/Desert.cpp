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

const int MAXN = 100005;
const int lim = 1000000000;

int n, s, m;
int ans[MAXN*4]; // [0,MAXN*2) seg, [MAXN*2,MAXN*4) agent
int acnt;

vector<int> edge[MAXN*4];

void qry (int l, int r, int agent) {
    debug(l, r, agent);
    for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
        if (l&1) {
            edge[agent].emplace_back(l++);
        }
        if (r&1) {
            edge[agent].emplace_back(--r);
        }
    }
}

vector<int> topo;
bool vis[MAXN*4];
int id[MAXN*4];

void dfs_topo (int nd) {
    vis[nd] = true;
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            dfs_topo(v);
        }
    }
    topo.emplace_back(nd);
    id[nd] = SZ(topo);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> s >> m;
    REP (i, s) {
        int p, d;
        cin >> p >> d;
        ans[p-1+n] = d;
    }
    for (int i=2;i<n*2;++i) {
        edge[i>>1].emplace_back(i);
    }
    acnt = n*2;

    REP (_m, m) {
        int l, r, k, x;
        cin >> l >> r >> k;
        l--,r--;
        int lst = l;
        REP (i, k) {
            cin >> x;
            x--;
            qry(lst,x,acnt);
            edge[x+n].emplace_back(acnt);
            lst = x+1;
        }
        qry(lst,r+1, acnt);
        acnt++;
    }
    debug("built");

    acnt--;
    REP1 (i, acnt) {
        if (!vis[i]) {
            dfs_topo(i);
        }
    }

    debug(topo);

    bool cyc = false;
    REP1 (i, acnt) {
        for (auto v : edge[i]) {
            debug(i, v);
            if (id[v] > id[i]) {
                cyc = true;
            }
        }
    }

    if (cyc) {
        cout << "NIE" << endl;
        return 0;
    }

    bool fail = false;
    for (auto v : topo) {
        bool imp = v >= n && v<n*2;
        if (edge[v].empty()) {
            if (ans[v] == 0) {
                ans[v] = imp ? 1 : 0;
            }
        } else {
            int mx = 0;
            for (auto u : edge[v]) {
                mx = max(mx, ans[u]);
            }
            if (ans[v] != 0) {
                if (ans[v] <= mx) {
                    fail = true;
                }
            } else {
                ans[v] = imp ? mx + 1 : mx;
                if (imp) {
                    fail |= (ans[v] > lim || ans[v] < 1);
                }
            }
        }
    }

    if (fail) {
        cout << "NIE" << endl;
    } else {
        cout << "TAK" << endl;
        REP (i, n) {
            cout << ans[i+n] << " \n"[i==n-1];
        }
    }


}
