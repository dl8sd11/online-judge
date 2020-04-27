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

int n, l, x[MAXN], b[MAXN];
int tr[MAXN];
double dp[MAXN];
bool solve (double rate) {
    dp[0] = 0;
    for (int i=1; i<=n; i++) {
        dp[i] = 1e18;

        for (int j=0; j<i; j++) {
            double nw = dp[j] + sqrt(abs(l-(x[i]-x[j]))) - rate * b[i];
            if (nw < dp[i]) {
                dp[i] = nw;
                tr[i] = j;
            }
        }
    }

    return dp[n] <= 0;
}

void solution () {
    vector<int> ord;
    int itr = n;

    while (itr != 0) {
        ord.eb(itr);
        itr = tr[itr];
    }

    reverse(ALL(ord));
    for (int i=0; i<SZ(ord); i++) {
        cout << ord[i] << " \n"[i==SZ(ord)-1];
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> l;
    for (int i=1; i<=n; i++) {
        cin >> x[i] >> b[i];
    }

    double L = 0, R = x[n]*1LL/b[n];
    debug(L, R, x[n], b[n]);
    for (int it=0; it<100; it++) {
        double M = (L + R) / 2;

        debug(M, solve(M));
        if (solve(M)) {
            R = M;
        } else {
            L = M;
        }
    }

    solve(R);
#ifdef tmd

    cout << fixed << setprecision(5) << R << endl;
#endif
    solution();

}

