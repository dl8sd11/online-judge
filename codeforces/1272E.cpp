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

typedef pair<int,int> pii;

const int MAXN = 200005;
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;

int n, a[MAXN], dis[MAXN];
bool vis[MAXN];

bool valid (int i) {
    return i >= 1 && i <= n;
}

bool head (int i, int j) {
    return valid(j) && ((a[i]^a[j])&1);
}

vector<int> edge[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    priority_queue<pii,vector<pii>,greater<pii> > pq;

    cin >> n;

    memset(dis, INF, sizeof(dis));
    REP1 (i, n) {
        cin >> a[i];
    }

    REP1 (i, n) {
        if (head(i,i+a[i]) || head(i,i-a[i])) {
            dis[i] = 1;
            pq.emplace(0, i);
        }
    }

    REP1 (nd, n) {
        vector<int> nxt = {nd+a[nd],nd-a[nd]};
        for (auto v : nxt) {
            if (valid(v)) {
                edge[v].emplace_back(nd);
            }
        }
    }

    /* Weight are all one but using Dijkstra's for practicing*/
    while (pq.size()) {
        int nd = pq.top().second;
        pq.pop();
        if (vis[nd]) {
            continue;
        }
        debug(nd);
        vis[nd] = true;

        for (auto v : edge[nd]) {
            if (dis[v] > dis[nd] + 1) {
                dis[v] = dis[nd] + 1;
                pq.emplace(dis[v], v);
            }
        }

    }

    REP1 (i, n) {
        cout << (dis[i] == INF ? -1 : dis[i]) << " \n"[i==n];
    }

}
