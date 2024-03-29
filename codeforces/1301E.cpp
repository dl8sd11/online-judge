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

const int MAXN = 502, MAXH = 251;
const ll MOD = 1000000007;

int n, m, q;

int sq[4][MAXN][MAXN];
int pr[MAXH][MAXN][MAXN];
int gr[MAXN][MAXN];

map<char,int> cmap = {{'R',0},{'G',1},{'Y',2},{'B',3}};

int sum (int d, int r1, int c1, int r2, int c2) {
    if (r2 < r1 || c2 < c1) {
        return 0;
    } else {
        return pr[d][r2][c2] - pr[d][r2][c1-1] - pr[d][r1-1][c2] + pr[d][r1-1][c1-1];
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> q;

    REP1 (i, n) {
        REP1 (j, m) {
            char ch;
            cin >> ch;
            gr[i][j] = cmap[ch];
        }
    }

    REP (c, 4) {
        for (int i=n; i>=1; i--) {
            for (int j=m; j>=1; j--) {
                if (gr[i][j] == c) {
                    sq[c][i][j] = min({sq[c][i+1][j], sq[c][i][j+1], sq[c][i+1][j+1]}) + 1;
                } else {
                    sq[c][i][j] = 0;
                }
            }
        }
    }

    REP1 (i, n) {
        REP1 (j, m) {
            int d = sq[0][i][j];
            if (sq[1][i][j+d] >= d && sq[2][i+d][j] >= d && sq[3][i+d][j+d] >= d) {
                pr[d][i][j] ++;
                #ifdef tmd

                if (d > 0) {
                    debug(i, j, d);
                }

                #endif // tmd
            }
            REP (sz, MAXH) {
                pr[sz][i][j] += pr[sz][i-1][j] + pr[sz][i][j-1] - pr[sz][i-1][j-1];
            }
        }
    }

    while (q--) {

        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        int l = 0, r = MAXH;

        while (l < r-1) {
            int mid = (l + r) >> 1;
            if (sum(mid, r1, c1, r2+1-mid*2, c2+1-mid*2) > 0) {
                l = mid;
            } else {
                r = mid;
            }
        }

        cout << l*l*4 << endl;
    }
}
