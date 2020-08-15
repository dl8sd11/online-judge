#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define MEM(i, n) memset(i, n, sizeof(i));
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

vector<int> edge[MAXN];
bool rmv[MAXN], one[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    int T;
    int n, m;

    cin >> T;
    while (T--) {
        cin >> n >> m;

        for (int i=0; i<m; i++) {
            int f, t;
            cin >> f >> t;
            edge[t].eb(f);
        }

        vector<int> ans;
        for (int i=1; i<=n; i++) {
            for (auto v : edge[i]) {
                if (one[v]) {
                    rmv[i] = true;
                    ans.eb(i);
                    break;
                }
            }

            if (rmv[i]) {
                continue;
            }
            for (auto v : edge[i]) {
                if (!rmv[v]) {
                    one[i] = true;
                    break;
                }

            }
        }
        cout << SZ(ans) << endl;
        for (int i=0; i<SZ(ans); i++) {
            cout << ans[i] << " \n"[i==SZ(ans)-1];
        }


        for (int i=1; i<=n; i++) {
            edge[i].clear();
            edge[i].shrink_to_fit();
            rmv[i] = false;
            one[i] = false;
        }
    }

}

