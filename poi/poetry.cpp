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

int n, s;

int bst;
vector<pii> ans;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> s;

    vector<pii> book;
    for (int i=0; i<n; i++) {
        int x;
        cin >> x;
        book.emplace_back(i, x);
    }

    bst = MOD;
    do {
        int rem = 0;
        int cur = 0;
        for (int i=0; i<n; i++) {
            if (rem == s - 1) {
                rem = 0;
                cur++;
            }
            rem += book[i].Y + 1;
            rem %= s;
        }
        if (cur < bst) {
            bst = cur;
            ans = book;
        }
    } while (next_permutation(ALL(book)));

    cout << bst << endl;
    REP (i, SZ(ans)) {
        cout << ans[i].X + 1 << " \n"[i==SZ(ans)-1];
    }
}
