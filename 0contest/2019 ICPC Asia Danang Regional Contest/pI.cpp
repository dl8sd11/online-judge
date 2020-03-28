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
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1003;
const ll MOD = 1000000007;


int n, ans[MAXN];
void query (int bit) {
    vector<int> src;
    REP1 (i, n) {
        if ((i>>bit) & 1) {
            src.eb(i);
        }
    }
    if (src.size()) {
        cout << "ASK " << SZ(src);
        for (auto v : src) {
            cout << " " << v;
        }
        cout << endl;
        cout.flush();

        REP (i, SZ(src)) {
            int x;
            cin >> x;
            ans[x] += 1<<bit;
        }
    }
}

void shout () {
    cout << "ANSWER";
    REP1 (i, n) {
        cout << " " << ans[i];
    }
    cout << endl;
    cout.flush();
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, 11) {
        query(i);
    }
    shout();
}
