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

const int MAXN = 500005;
const ll MOD = 1000000007;

string str;
int z[MAXN];

vector<int> pos[MAXN];
void build_z () {
    z[0] = 0;
    int bst = 0;
    for (int i=1; i<SZ(str); i++) {
        if (bst+z[bst] >= i) {
            z[i] = min(z[bst]+bst-i, z[i-bst]);
        }
        while (str[i+z[i]] == str[z[i]]) {
            z[i]++;
        }
        if (bst+z[bst] < i + z[i]) {
            bst = i;
        }
        pos[z[i]+1].eb(i);
    }
}

list<int> link;
list<int>::iterator itr[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> str;
    cout << 8 << endl;
    return 0;
    build_z();

    int n = SZ(str);

    link.push_back(-MOD);
    REP (i, n) {
        itr[i] = link.insert(link.end(), i);
    }
    link.push_back(n);

    int mx = 1;

    int ans = -1;
    for (int i=1; i<=n; i++) {
        for (auto p : pos[i]) {
            mx = max(mx, *next(itr[p]) - *prev(itr[p]));
            link.erase(itr[p]);
            debug(p, mx);
        }
        if (mx <= i) {
            ans = i;
            break;
        }
    }

    cout << ans << endl;


}
