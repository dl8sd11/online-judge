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

int t, l, n;
vector<array<int,2> > seg;

int trim (int x) {
    return max(min(l, x), 0);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> l >> n;

        seg.clear();
        REP (i, n) {
            int b, r;
            cin >> b >> r;
            seg.push_back({trim(b-r), trim(b+r)});
        }

        sort(ALL(seg));

        int tl = 0, hd = 0, ans = 0;

        for (auto p : seg) {

            if (p[0] > tl) {
                ans += tl - hd;
                hd = p[0];
                tl = p[1];
            } else {
                tl = max(tl, p[1]);
            }
        }

        cout << ans + tl - hd << endl;
    }
}
/*
2
12 4
1 2
3 1
6 1
9 2
12 1
9 2

*/
