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

const int MAXN = 200005;
const ll MOD = 1000000007;

int n, m, w[MAXN], req[MAXN];
pair<int,int> dep[MAXN];
vector<int> cust[MAXN];

bool visd[MAXN], visg[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    REP1 (i, n) {
        cin >> w[i];
    }

    REP1 (i, m) {
        cin >> dep[i].X >> dep[i].Y;
        req[dep[i].X]++;
        req[dep[i].Y]++;
        cust[dep[i].X].eb(i);
        cust[dep[i].Y].eb(i);
    }
    
    vector<int> ans, stk;
    REP1 (i, n) {
        if (w[i] >= req[i]) {
            stk.eb(i);
            visd[i] = true;
        }
    }

    while (stk.size()) {
        int d = stk.back();
        stk.pop_back();

        for (auto c : cust[d]) {
            if (visg[c]) {
                continue;
            }
            visg[c] = true;

            ans.eb(c);
            int x, y;
            tie(x, y) = dep[c];

            req[x]--;
            req[y]--;
            if (req[x] <= w[x] && !visd[x]) {
                stk.eb(x);
            }
            if (req[y] <= w[y] && !visd[y]) {
                stk.eb(y);
            }
        }
    }
    if (ans.size() == m) {
        cout << "ALIVE" << endl;
        reverse(ALL(ans));
        REP (i, m) {
            cout << ans[i] << " \n"[i==m-1];
        }
    } else {
        cout << "DEAD" << endl;
    }

}

