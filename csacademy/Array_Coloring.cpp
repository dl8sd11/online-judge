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

int n, m, a[MAXN], res[MAXN];
vector<int> pos[MAXN];

void solve (int l, int r) {
    vector<int> cur;
    for (int x=l; x<r; ) {
        cur.eb(a[x]);
        x = pos[a[x]].back() + 1;
    }

    res[l] += SZ(cur);
    res[r] -= SZ(cur);

    for (auto v : cur) {
        for (int i=1; i<SZ(pos[v]); i++) {
            if (pos[v][i] != pos[v][i-1]+1) {
                solve(pos[v][i-1]+1, pos[v][i]);
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n) {
        cin >> a[i];
        pos[a[i]].eb(i);
    }

    solve(0, n);

    int sum = 0, ans = 0;
    REP (i, n) {
        sum += res[i];
        ans = max(ans, sum);
    }

    REP1 (i, m) {
        ans += pos[i].empty();
    }

    cout << ans << endl;
}
