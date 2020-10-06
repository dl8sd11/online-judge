#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define SZ(i) int(i.size())
#define ALL(i) i.begin(), i.end()
#define MEM(i,a) memset(i, (a), sizeof(i))
#define X first
#define Y second
#define eb emplace_back
#define pb push_back
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<", ";_do(y...);}
template<typename IT> ostream& __printRng (ostream &os, IT bg, IT ed) {
    for (IT it=bg; it!=ed; it++) {
        if (it!=bg) os << "," << *it;
        else os << "{" << *it;
    }
    return os << "}";
}
template<typename T> ostream &operator << (ostream &os, const pair<T,T> &v) {
    return os << "{" << v.X << "," <<v.Y << "}";
}
template<typename T> ostream &operator << (ostream &os, const vector<T> &v) {
    return __printRng(os, ALL(v));
}
template<typename T> ostream &operator << (ostream &os, const set<T> &v) {
    return __printRng(os, ALL(v));
}
#define IOS()
#else
#define debug(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif

const int MAXN = 100005;

struct Line {
    pii a, b;
};
vector<Line> lines;

double dd (pii x, pii y) {
    pii nw = {x.X - y.X, x.Y - y.Y};
    return sqrt(double(nw.X)*nw.X + double(nw.Y)*nw.Y);
}

struct Edges {
    int u, v;
    double dis;
    int mask;

    Edges (int x, int y): u(x), v(y) {
        dis = 1e18;
        for (int i=0; i<2; i++) {
            for (int j=0; j<2; j++) {
                double d = dd(i?lines[u].b:lines[u].a,
                              j?lines[v].b:lines[v].a);
                if (d < dis) {
                    dis = d;
                    mask = (i<<1) + j;
                }

            }
        }
    }

    void print () {
        pii f = (mask&2) ? lines[u].b : lines[u].a;
        pii t = (mask&1) ? lines[v].b : lines[v].a;
        cout << f.X << " " << f.Y << " " << t.X << " " << t.Y << endl;
    }
};

int djs[MAXN], sz[MAXN];

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

bool mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x == y) return false;
    if (sz[x] > sz[y]) swap(x, y);
    djs[x] = y;
    sz[y] += sz[x];
    return true;
}
int main () {
    IOS();
    int n;
    cin >> n;

    lines.resize(n);
    for (int i=0; i<n; i++) {
        cin >> lines[i].a.X >> lines[i].a.Y >> lines[i].b.X >> lines[i].b.Y;
        djs[i] = i;
        sz[i] = 1;
    }

    vector<Edges> edges;
    for (int i=0; i<n; i++) {
        for (int j=0; j<i; j++) {
            Edges cur(i, j);
            edges.eb(cur);
        }
    }
    sort(ALL(edges), [&](const Edges &e1, const Edges &e2) {
        return e1.dis < e2.dis;
    });
    for (auto e : edges) {
        debug(e.u, e.v, e.dis);
        if (mrg(e.u, e.v)) {
            e.print();
        }
    }
}

