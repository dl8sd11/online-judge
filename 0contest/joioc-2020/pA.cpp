#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define X first
#define Y second
#define eb emplace_back
#define MEM(i,a) memset(i, (a), sizeof(i))
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream& __printRng (ostream& os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        if (it==bg) os << *it;
        else os << "," << *it;
    }
    return os << "}";
}
template<typename T> ostream& operator << (ostream& os, const vector<T> &v) {return __printRng(os, ALL(v));}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

int n, m;
vector<vector<int> > s, dp;

bool solve () {
    fill(ALL(dp), vector<int>(m, 0));
    dp[0][0] = true;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (!s[i][j]) {
                if (i) dp[i][j] |= dp[i-1][j];
                if (j) dp[i][j] |= dp[i][j-1];
            }
        }
    }
    debug(dp);
    return dp[n-1][m-1];
}
int main () {
    IOS();
    cin >> n >> m;

    s.resize(n, vector<int>(m,0));
    dp.resize(n, vector<int>(m,0));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> s[i][j];
        }
    }

    int q;
    cin >> q;
    for (int u=0; u<q; u++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        s[x][y] = true;
        if (solve()) cout << 1 << endl;
        else {
            cout << 0 << endl;
            s[x][y] = false;
        }
    }

}
