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

int t;

void rd (int &x, int &y) {
    string s;
    cin >> s;
    debug(s);
    x = (s[0]-'0')*10 + s[1]-'0';
    y = (s[3]-'0')*10 + s[4]-'0';
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        int h1, m1, h2, m2;


        rd(h1,m1);
        rd(h2,m2);

        debug(h1, m1, h2, m2);

        m1 = h1 * 60 + m1;
        m2 = h2 * 60 + m2;


        int deg;
        cin >> deg;
        debug(m1, m2, deg);

        vector<int> m11;
        m11.eb(deg*2);

        while (m11.back() < m2*11) {
            if (deg == 90) {
                m11.eb(m11.back() + 360);
            } else {
                m11.eb(m11.back() + 720);
            }
        }
        debug(m11);

        int ans = 0;
        for (auto x : m11) {
            if (x >= m1*11 && x <= m2*11) {
                ans++;
            }
        }

        cout << ans << endl;
    }
}
