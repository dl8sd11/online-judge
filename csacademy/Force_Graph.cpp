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

int n, m, f1, f2;
vector<int> edge[MAXN];

pii pos[MAXN];
vector<pii> xval;
vector<pii> yval;

ll ansx[MAXN], ansy[MAXN];

void build(ll *ans, const vector<pii> &val) {
    ll sum = 0;
    for (auto p : val) {
        sum += p.X;
    }

    for (auto p : val) {
        ans[p.Y] = f2 * (1LL*p.X*n-sum);
    }
}
//
//ostream& operator << (ostream &os, ll x) {
//    if (x < 0) {
//        os << "-";
//        x = -x;
//    }
//    string res;
//    while (x > 0) {
//        res += char(x%10+'0');
//        x /= 10;
//    }
//    if (res.empty()) {
//        res = "0";
//    }
//    reverse(ALL(res));
//    return os << res;
//}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> f1 >> f2;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    REP1 (i, n) {
        cin >> pos[i].X >> pos[i].Y;
        xval.eb(pos[i].X, i);
        yval.eb(pos[i].Y, i);
    }

    sort(xval.begin(), xval.end());
    sort(yval.begin(), yval.end());

    build(ansx, xval);
    build(ansy, yval);


    REP1 (i, n) {
        for (auto v : edge[i]) {
            ansx[i] += 1LL* (pos[i].X-pos[v].X) * (f1-f2);
            ansy[i] += 1LL * (pos[i].Y-pos[v].Y) * (f1-f2);
        }
        cout << ansx[i] << " " << ansy[i] << endl;
    }
}
