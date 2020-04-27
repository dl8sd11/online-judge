#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define eb emplace_back
#define SZ(i) int(i.size())
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define debug(...) do{\
    fprintf(stderr, "%d-(%s)=",__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const int MAXN = 1e5 + 5;

namespace RTree {
    struct Edge {
        int to, id;
        ll c;
    };
    vector<Edge> edge[MAXN];

    void dfs (int nd, int par) {
        for (int i=0; i<SZ(edge[nd]); i++) {
            if (edge[nd][i].to == par) {
                edge[nd].erase(edge[nd].begin()+i);
            }
        }
        for (int i=0; i<SZ(edge[nd]); i++) {
            dfs(edge[nd][i].to, nd);
        }
    }

    void input (int n) {
        for (int i=0; i<n-1; i++) {
            int a, b;
            ll c;
            cin >> a >> b >> c;
            edge[a].push_back({b, i, c});
            edge[b].push_back({a, i, c});
        }
        dfs(1, 1);
    }
}

#define RAKE 0
#define COMPRESS 1

struct Cluster {
    ll du, dv, len, ans;
    int type;
    Cluster *lc, *rc, *p;
    Cluster():du(0),dv(0),len(0),ans(0),type(-1),lc(0),rc(0),p(0){}
};

void compress (Cluster *a, Cluster *b, Cluster *c) { // compress a, b as c, a on top
    c->type = COMPRESS;
    c->lc = a;
    c->rc = b;
    a->p = b->p = c;
    c->du = max(a->du, a->len + b->du);
    c->dv = max(b->dv, b->len + a->dv);
    c->len = a->len + b->len;
    c->ans = max({a->ans, b->ans, a->dv + b->du});
}

void rake (Cluster *a, Cluster *b, Cluster *c) { // rake a into b as c
    c->type = RAKE;
    c->lc = a;
    c->rc = b;
    a->p = b->p = c;
    c->du = max(a->du, b->du);
    c->dv = max(b->len + a->du, b->dv);
    c->len = b->len;
    c->ans = max({a->ans, b->ans, a->du + b->du});
}

Cluster *lf[MAXN], *cl[MAXN];
vector<int> edge[MAXN];
int ch[MAXN], cnt;
bool vis[MAXN];

void dfs (int nd) {
    vis[nd] = false;
    for (int v : edge[nd]) {
        dfs(v);
    }

    // try compress
    if (nd != 1 && SZ(edge[nd]) == 1) {
        if (!vis[edge[nd][0]]) { // TODO why needed
            vis[nd] = vis[edge[nd][0]] = true;
            Cluster *nw = new Cluster;
            
            compress(cl[nd], cl[edge[nd][0]], nw);
            cl[nd] = nw;
            cnt--;

            swap(edge[nd], edge[edge[nd][0]]);
        }
        return;
    }

    vector<int> nch;
    queue<int> qa, qb;

    for (int v : edge[nd]) {
        if (vis[v]) {
            nch.eb(v);
        } else if (SZ(edge[v]) == 0) {
            qa.emplace(v);
        } else {
            qb.emplace(v);
        }
    }

    while (SZ(qa) >= 1 && SZ(qa) + SZ(qb) >= 2) {
        int a = qa.front();
        qa.pop();

        int b;
        if (qb.empty()) {
            b = qa.front();
            qa.pop();
        } else {
            b = qb.front();
            qb.pop();
        }

        vis[a] = vis[b] = true;
        Cluster *nw = new Cluster;
        rake(cl[a], cl[b], nw);
        nch.eb(b);
        cl[b] = nw;
        cnt--;
    }

    while (SZ(qa)) {
        nch.eb(qa.front());
        qa.pop();
    }
    while (SZ(qb)) {
        nch.eb(qb.front());
        qb.pop();
    }
    edge[nd] = nch;
}

void update (Cluster *nd) {
    while (nd->p) {
        nd = nd->p;
        if (nd->type == COMPRESS) {
            compress(nd->lc, nd->rc, nd);
        } else {
            rake(nd->lc, nd->rc, nd);
        }
    }
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n, q;
    ll w;

    cin >> n >> q >> w;
    RTree::input(n);

    for (int i=1; i<=n; i++) {
        for (const auto &e : RTree::edge[i]) {
            edge[i].eb(e.to);
            lf[e.to] = new Cluster;
            lf[e.to]->du = lf[e.to]->dv = lf[e.to]->len = lf[e.to]->ans = e.c;
            ch[e.id] = e.to;
            cl[e.to] = lf[e.to];
        }
    }

    cnt = n-1; // size of cluster
    while (cnt > 1) {
        dfs(1);
    }

    ll last = 0;
    while (q--) {
        int d;
        ll e;
        cin >> d >> e;

        d = (d + last) % (n - 1);
        e = (e + last) % w;

        Cluster *nd = lf[ch[d]];
        nd->du = nd->dv = nd->len = nd->ans = e;
        update(nd);

        last = cl[edge[1][0]]->ans;

        cout << last << endl;
    }
    
    return 0;
}
