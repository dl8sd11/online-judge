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

int n, q;
ll m;

vector<array<int,2> > dt[2];

int sz, djs[MAXN];

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void uni (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x != y) {
        sz--;
        djs[x] = y;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> q;
    REP (i, q) {
        int a, b, c;
        cin >> a >> b >> c;
        dt[c].push_back({a,b});
    }

    REP1 (i, n) {
        djs[i] = i;
        sz++;
    }

    for (auto v : dt[0]) {
        uni(v[0], v[1]);
    }

    for (auto v : dt[1]) {
        if (fnd(v[0]) == fnd(v[1])) {
            cout << "No" << endl;
            return 0;
        }
    }


    if (m == n - 1) {
        if (dt[1].empty()) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    } else if (m <= n + 1LL*sz*(sz-3)/2) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
