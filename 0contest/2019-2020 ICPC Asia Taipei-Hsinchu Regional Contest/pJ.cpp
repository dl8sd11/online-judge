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

const int MAXN = 502;
const ll MOD = 1000000007;

int t, n, m, ans;
bitset<MAXN> msk[16];

void dfs (int idx, bitset<MAXN> cur, int cnt) {
    if (idx == m) {
        if (cur.count() == n) {
            ans = min(ans, cnt);
            //debug(cur.to_string());
        }
    } else {
        dfs(idx+1, cur, cnt);
        cur |= msk[idx];
        dfs(idx+1, cur, cnt+1);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {

        cin >> n >> m;
        REP (i, m) {
            msk[i].reset();
            REP (j, n) {
                char d;
                cin >> d;
                msk[i][j] = d == '1';
            }
//            debug(msk[i].to_string());
        }

        ans = MOD;
        bitset<MAXN> nw;
        dfs(0, nw, 0);

        cout << (ans == MOD ? -1 : ans) << endl;
    }
}
