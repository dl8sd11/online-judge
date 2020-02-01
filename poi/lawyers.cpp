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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int,int> pii;

const int MAXN = 1000006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, k;
pii itv[MAXN];

tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update> rk;
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> k;
    REP (i, n) {
        cin >> itv[i].first >> itv[i].second;
    }

    sort(itv, itv+n);

    int mx = 0;
    int bst = 0;
    for (int i=0; i<n; i++) {
        rk.insert({itv[i].second, i});
        if (i >= k-1) {
            int r = rk.find_by_order(i-k+1)->first;
            debug(itv[i].first, r);
            if (r - itv[i].first > mx) {
                mx = r - itv[i].first;
                bst = i;
            }
        }
    }

    cout << mx << endl;
    /*
        also output the index
    */
}
