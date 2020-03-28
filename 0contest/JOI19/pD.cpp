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

const int MAXN = 1003;
const ll MOD = 1000000007;

int n;
vector<pll> pos;

void solve (vector<int> x, ll &res) {
    sort(ALL(x));

    for (int i=1; i<=n; i++) {
        res += abs(x[i-1] - i);
    }
}

bool fll[MAXN][3];
void ckmin (ll &x, ll y) {
    x = x > y ? y : x;
}

ll dis (pll a, pll b) {
    return abs(a.X-b.X) + abs(a.Y-b.Y);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    REP (i, n*2) {
        int x, y;
        cin >> x >> y;

        bool ig = false;
        if (x >= 1 && x <= n && y >= 1 && y <= 2) {
            if (!fll[x][y]) {
                ig = true;
                fll[x][y] = true;
            }
        }
        if (!ig) {
            pos.eb(x, y);
        }
    }

    sort(ALL(pos));

    ll ans = 0;

    int idx = 0;
    for (int i=1; i<=n; i++) {
        if (fll[i][1] & fll[i][2]) {
            continue;
        } else if (fll[i][2]) {
            ans += dis(pos[idx], pll(i, 1));
            idx++;
        } else if (fll[i][1]){
            ans += dis(pos[idx], pll(i, 2));
            idx++;
        } else {
            ll pa = dis(pos[idx],pll(i,1)) + dis(pos[idx+1], pll(i,2));
            ll pb = dis(pos[idx],pll(i,2)) + dis(pos[idx+1], pll(i,1));
            ans += min(pa, pb);
            idx+=2;
        }
    }

    cout << ans << endl;
}
