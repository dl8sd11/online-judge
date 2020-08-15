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

int n, m, k;
vector<int> edge[MAXN];

int fat[MAXN], dep[MAXN];

vector<int> gp[2];
void color (int nd, int par, bool col) {
    gp[col].eb(nd);
    for (auto v : edge[nd]) {
        if (v != par) {
            color(v, nd, !col);
        }
    }
}

pair<int,int> back (int nd, int par) {
    fat[nd] = par;
    dep[nd] = dep[par] + 1;
    debug(nd, par);

    pair<int,int> ret = {n+1, 0};
    for (auto v : edge[nd]) {
        if (dep[v] == 0) {
            pair<int,int> tmp = back(v, nd);
            if (dep[tmp.X] - dep[tmp.Y] < dep[ret.X] - dep[ret.Y]) {
                ret = tmp;
            }
        } else if (v != par && dep[nd] > dep[v]) {
            if (dep[nd] - dep[v] < dep[ret.X] - dep[ret.Y]) {
                debug(v, nd, par);
                ret = {nd, v};
            }
        }
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> k;
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }
    dep[n+1] = 0x3f3f3f3f;

    if (n == m + 1) {
        // tree
        color(1, -1, 0);
        if (SZ(gp[0]) < SZ(gp[1])) {
            swap(gp[0], gp[1]);
        }

        cout << 1 << endl;
        REP (i, (k+1)/2) {
            cout << gp[0][i] << " ";
        }
            cout << endl;
    } else {
        pair<int,int> cy = back(1, 0);
        int len = dep[cy.X] - dep[cy.Y] + 1;
        debug(cy.X, cy.Y);
        if (len <= k) {
            cout << 2 << endl;
            cout << len << endl;
            REP (i, len) {
                cout << cy.X << " ";
                cy.X = fat[cy.X];
            }
        } else {
            cout << 1 << endl;
            REP (i, (k+1)/2) {
                cout << cy.X << " ";
                cy.X = fat[cy.X];
                cy.X = fat[cy.X];
            }
        }
        cout << endl;
    }
}

