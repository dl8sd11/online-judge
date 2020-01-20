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

const int MAXN = 202;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, ans;
bool blk[MAXN][MAXN];
int pre[MAXN][MAXN];

void check (int r1, int r2) {
    debug(r1, r2);
    int cnt = 0;
    vector<int> pos;
    for (int i=1; i<=m+1; i++) {
        if (i == m+1 || !(blk[r1][i] && blk[r2][i])) {
            if (pos.size()) {
                debug(pos.back(), pos.front(), cnt);
                ans = max(ans, (pos.back()-pos.front()+1) * (r1-r2+1));
                debug(ans);
            }
            cnt = 0;
            pos.clear();
        } else {
            if (pre[r1][i] - pre[r2-1][i] == r1-r2+1) {
                pos.emplace_back(i);
            }
            cnt++;
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    #ifndef tmd

    freopen("fortmoo.in","r",stdin);
    freopen("fortmoo.out","w",stdout);

    #endif // tmd

    cin >> n >> m;
    REP1 (i, n) {
        REP1 (j, m) {
            char c;
            cin >> c;
            blk[i][j] = c == '.';
            pre[i][j] = pre[i-1][j] + blk[i][j];
        }
    }

    REP1 (i, n) {
        REP1 (j, i-1) {
            check(i, j);
        }
    }

    cout << ans << endl;
}
