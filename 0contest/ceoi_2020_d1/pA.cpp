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

const int MOD = 1000000007;
const int MAXN = 100005;

int add (int x, int y) {
    return (x+=y) >= MOD ? x-MOD : x;
}

int sub (int x, int y) {
    return (x-=y) < 0 ? x + MOD : x;
}

int mul (int x, int y) {
    return ll(x) * y % MOD;
}

int chs (int x) { // x choose 2
    return x&1 ? mul(x,(x-1)/2) : mul(x/2, (x-1));
}

int sum (int l, int r) {
    int a = l + r;
    int b = r - l + 1;
    return (ll(a) * b / 2) % MOD;
}

int djs[MAXN], sz[MAXN], w[MAXN];
bool vis[MAXN];
int n;

void init () {
    for (int i=0; i<n; i++) {
        djs[i] = i;
        sz[i] = 1;
    }
}

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

int cb = 0;
void mrg (int x, int y) {
    debug(x, y);
    x = fnd(x), y = fnd(y);
    assert(x != y);
    if (sz[x] > sz[y]) swap(x, y);    
    djs[x] = y;
    sz[y] += sz[x];
    cb = add(cb, mul(w[x], w[y]));
    w[y] = add(w[y], w[x]);
}

int main () {
    IOS();

    cin >> n;
    init();

    vector<pii> rect(n+1);
    for (int i=0; i<n; i++) cin >> rect[i].X;
    for (int i=0; i<n; i++) cin >> rect[i].Y;
    rect[n] = {0, 0};

    vector<int> id(n+1);
    iota(ALL(id), 0);
    sort(ALL(id), [&](int i, int j) {
        return rect[i].X > rect[j].X;
    });

    int ans = 0;
    for (int i=0, j; i<n; ) {
        int hd = i;
        for (j=hd; j<n && rect[id[j]].X == rect[id[hd]].X; j++) {
            int x = id[j];
            debug(rect[x], chs(rect[x].Y+1));
            vis[x] = true;
            w[x] = rect[x].Y;
            cb = add(cb, chs(rect[x].Y+1));
            if (x > 0 && vis[x-1]) mrg(x-1, x);
            if (x < n-1 && vis[x+1]) mrg(x, x+1);
        }

        int sm = sum(rect[id[j]].X+1, rect[id[hd]].X);
        debug(cb, sm);
        ans = add(ans, mul(cb, sm));
        i = j;
    }

    cout << ans << endl;
}


