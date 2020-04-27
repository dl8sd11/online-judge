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

const int MAXN = 1000006;
const int MAXLG = __lg(MAXN) + 2;
const ll MOD = 1000000007;

int n, l[MAXN], r[MAXN];
pii hval[MAXN];
int anc[MAXLG][MAXN];
bool rgt[MAXN];

const int C[2] = {880301, 910607};
const int MD[2] = {1000000007, 1000000009};

pii mC (pii org) {
    return {org.X*1LL*C[0]%MD[0], org.Y*1LL*C[1]%MD[1]};
}

pii add (pii org) {
    return {(org.X+1)%MD[0], (org.Y+1)%MD[1]};
}

void dfs (int nd) {
    if (nd == 0) {
        return;
    }

    anc[0][l[nd]] = nd;
    anc[0][r[nd]] = nd;
    rgt[r[nd]] = true;

    pii res = mC(hval[nd]);
    hval[l[nd]] = res;
    hval[r[nd]] = add(res);

    dfs(l[nd]);
    dfs(r[nd]);
}

bool gt (int u, int v) {
    for (int i=MAXLG-1; i>=0; i--) {
        if (hval[anc[i][u]] != hval[anc[i][v]]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }

    return rgt[u] > rgt[v];
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    for (int i=1; i<=n; i++) {
        cin >> l[i] >> r[i];
    }

    dfs(1);
    anc[0][1] = 1;
    for (int i=1; i<MAXLG; i++) {
        for (int j=1; j<=n; j++) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }

    int q;
    cin >> q;

    while (q--) {

        int u, v;
        cin >> u >> v;

        if (hval[u] == hval[v]) {
            cout << "TAK" << endl;
        } else {
            cout << (gt(u,v) ? "TAK" : "NIE") << endl;
        }
    }
}

