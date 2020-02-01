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

const int MAXN = 100005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, h;
struct Cow {
    int h, w, s;
    bool operator < (const Cow &cw) const {
        return w+s > cw.w+cw.s;
    }
};
Cow cow[21];

int ans;

void dfs (int idx, int mn, int H) {
    debug(idx, mn, H);
    if (idx == n) {
        if (H >= h) {
            ans = max(ans, mn);
        }
    } else {
        dfs(idx+1, mn, H);
        dfs(idx+1, min(mn-cow[idx].w,cow[idx].s), H+cow[idx].h);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    #ifndef tmd

    freopen("guard.in","r",stdin);
    freopen("guard.out","w",stdout);

    #endif // tmd

    cin >> n >> h;
    REP (i, n) {
        cin >> cow[i].h >> cow[i].w >> cow[i].s;
    }

    sort(cow, cow+n);
    ans = -1;
    dfs(0, 0x3f3f3f3f, 0);

    if (ans == -1) {
        cout << "Mark is too tall" << endl;
    } else {
        cout << ans << endl;
    }
}
