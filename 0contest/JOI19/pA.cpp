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

const int MAXN = 3003;
const ll MOD = 1000000007;

int n, m;
char c[MAXN][MAXN];
int O[MAXN][MAXN], I[MAXN][MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n) {
        REP (j, m) {
            cin >> c[i][j];
        }
    }

    for (int i=0; i<n; i++) {
        int sum = 0;
        for (int j=m-1; j>=0; j--) {
            sum += c[i][j] == 'O';
            O[i][j] = sum;
        }
    }

    for (int j=0; j<m; j++) {
        int sum = 0;
        for (int i=n-1; i>=0; i--) {
            sum += c[i][j] == 'I';
            I[i][j] = sum;
        }
    }

    ll ans = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (c[i][j] == 'J') {
                ans += O[i][j] * I[i][j];
            }
        }
    }

    cout << ans << endl;


}

/*
3 4
JOIJ
JIOO
IIII
*/
