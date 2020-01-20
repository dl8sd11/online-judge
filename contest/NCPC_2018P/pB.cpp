#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define MEM(a,b) memset(a,(b),sizeof(a))
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define eb emplace_back
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d (%s) = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#define endl '\n'
#endif

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 102;
const int MOD = 1000000007;

int t;
string a, b;


vector<set<int> > ha, hb;

void build(vector<set<int> > &hs, string str) {
    int sz = SZ(str);
    hs.resize(sz);
    REP (l, sz) {
        int sum = 0;
        for (int j=l; j<sz; j++) {
            sum = (sum * 2 + str[j]-'0') % MOD;
            debug(l, j, sum);
            hs[j-l].insert(sum);
        }
    }
}

int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> a >> b;
        ha.clear();
        hb.clear();
        build(ha, a);
        build(hb, b);

        int ans = 0;
        REP (i, min(SZ(a),SZ(b))) {
            for (auto v : ha[i]) {
                if (hb[i].count(v)) {
                    ans = max(ans, i+1);
                }
            }
        }

        cout << ans << endl;

    }

}

/*
3
001 10010
11111 0111101
000 111
*/
