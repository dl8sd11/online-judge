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


const int MAXN = 2003;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXC = 200005;

int n;

int sieve[MAXC], x, y;

void build () {
    for (int i=2;i*i<MAXC;i++) {
        for (int j=i*i;j<MAXC;j+=i) {
            sieve[j] = true;
        }
    }
}

vector<int> odd, even;
int xp[MAXN], yp[MAXN];
bool vis[MAXN];
vector<int> edg[MAXN], redg[MAXN];

bool dfs (int u) {
    if (vis[u]) {
        return false;
    }
    vis[u] = true;

    for (auto v : edg[u]) {
        if (yp[v] == -1 || dfs(yp[v])) {
            xp[u] = v;
            yp[v] = u;
            return true;
        }
    }
    return false;
}

bool vx[MAXN], vy[MAXN];
void vc (int nd, bool isX) {
    if (isX) {
        if (vx[nd]) {
            return;
        }
        vx[nd] = true;
        for (auto v : edg[nd]) {
            if (xp[nd] != v) {
                vc(v, !isX);
            }
        }
    } else {
        if (vy[nd]) {
            return;
        }
        vy[nd] = true;
        for (auto v : redg[nd]) {
            if (yp[nd] == v) {
                vc(v, !isX);
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    build();

    cin >> n;
    REP (i, n) {
        int d;
        cin >> d;
        if (d & 1) {
            odd.emplace_back(d);
        } else {
            even.emplace_back(d);
        }
    }

    x = SZ(odd), y = SZ(even);
    REP (i, x) {
        REP (j, y) {
            if (!sieve[odd[i]+even[j]]) {
                edg[i].emplace_back(j);
                redg[j].emplace_back(i);
                debug(i, j, odd[i], even[j]);

            }
        }
    }

    int cnt = 0;

    memset(xp, -1, sizeof(xp));
    memset(yp, -1, sizeof(yp));
    REP (i, x) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) {
            cnt++;
        }
    }

    memset(vx, 0, sizeof(vx));
    memset(vy, 0, sizeof(vy));
    REP (i, x) {
        if (xp[i] == -1) {
            vc(i, 1);
        }
    }

    vector<int> ans;
    REP (i, x) {
        if (!vx[i]) {
            ans.emplace_back(odd[i]);
        }
    }
    REP (i, y) {
        if (vy[i]) {
            ans.emplace_back(even[i]);
        }
    }
    debug(ans);
    assert(cnt == SZ(ans));

    cout << cnt << endl;
    REP (i, SZ(ans)) {
        cout << ans[i] << " \n"[i==SZ(ans)-1];
    }
}
