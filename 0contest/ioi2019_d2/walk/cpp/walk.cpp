#include "walk.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ll,int> pli;
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
map<int,int> pil[MAXN];

vector<int> add[MAXN], rmv[MAXN];
int nnd;

int n, m;
vector<pii> edge[MAXN*12];

ll dis[MAXN*12];
bool vis[MAXN*12];
priority_queue<pli, vector<pli>, greater<pli> > pq;

void add_edge (int u, int v, int w) {
    edge[u].eb(v, w);
    edge[v].eb(u, w);
    debug(u, v, w);
}

ll dijk (int s, int t) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0;
    pq.emplace(0, s);

    while (pq.size()) {
        int nd = pq.top().Y;
        pq.pop();
//        debug(nd);
        if (vis[nd]) {
            continue;
        }
        vis[nd] = true;

        for (auto e : edge[nd]) {
//            debug(e.X, e.Y, dis[e.X]);
            if (dis[e.X] > dis[nd] + e.Y) {
                dis[e.X] = dis[nd] + e.Y;
                pq.emplace(dis[e.X], e.X);
//                debug(dis[e.X], e.X);
            }
        }
    }

    return dis[t] == 0x3f3f3f3f3f3f3f3f ? -1 : dis[t];
}

set<pii> sid;
int lid[MAXN];

long long min_distance(std::vector<int> x, std::vector<int> h, std::vector<int> l, std::vector<int> r, std::vector<int> y, int s, int g) {
    n = SZ(x);
    m = SZ(y);

    REP (i, m) {
        add[l[i]].eb(i);
        rmv[r[i]].eb(i);
    }

    memset(lid, -1, sizeof(lid));
    nnd = n;
    REP (i, n) {
        for (auto v : add[i]) {
            sid.insert({y[v], v});
        }


        for (auto v : sid) {
            if (v.X <= h[i]) {
                if (pil[i].count(v.X) == 0) {
                    pil[i][v.X] = nnd++;
                }
                if (lid[v.Y] != -1) {
                    add_edge(nnd-1, pil[lid[v.Y]][v.X], x[i] - x[lid[v.Y]]);
                }
                lid[v.Y] = i;
            } else {
                break;
            }
        }


        for (auto v : rmv[i]) {
            sid.erase({y[v], v});
        }
    }

    REP (i, n) {
        int lv = i;
        int lh = 0;
        for (auto v : pil[i]) {
            debug(v.X, v.Y);
            add_edge(lv, v.Y, v.X - lh);

            lh = v.X;
            lv = v.Y;

        }
    }

    return dijk(s, g);
}
