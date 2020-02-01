#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define eb emplace_back
#define MEM(a,b) memset(a,(b),sizeof(a))
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
template<typename IT> ostream&  __printRng(ostream &os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg;it!=ed;it++) {
        cout << (it==bg?"":",") << *it;
    }
    os << "}";
    return os;
}
template<typename T> ostream& operator << (ostream &os, vector<T> &vec) {
    return __printRng(os, vec.begin(), vec.end());
}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;

string line;

vector<int> num;
vector<char> op;

const int MAXN = 51;

ll mx[MAXN][MAXN], mn[MAXN][MAXN];

void MN (ll &x, ll y) {
    x = min(x, y);
}

void MX (ll &x, ll y) {
    x = max(x, y);
}

void solve (int l, int r) {
    if (mx[l][r] != -INF) {
        return;
    }
    if (l == r) {
        mx[l][r] = mn[l][r] = num[l];
    }

    for (int i=l;i<r; i++) {
        solve(l, i);
        solve(i+1, r);
        if (op[i] == '+') {
            MX(mx[l][r],mx[l][i] + mx[i+1][r]);
            MN(mn[l][r],mn[l][i] + mn[i+1][r]);
        } else if (op[i] == '-') {
            MX(mx[l][r],mx[l][i] - mn[i+1][r]);
            MN(mn[l][r],mn[l][i] - mx[i+1][r]);
        } else {
            MX(mx[l][r],mx[l][i] * mx[i+1][r]);
            MX(mx[l][r],mn[l][i] * mn[i+1][r]);
            MN(mn[l][r],mx[l][i] * mn[i+1][r]);
            MN(mn[l][r],mn[l][i] * mx[i+1][r]);
        }
    }
    debug(l, r, mx[l][r], mn[l][r]);
}
/*********Good***Luck*********/
int main () {
    IOS();

    getline(cin, line);

    {
        int sum = 0;
        for (auto v : line) {
            if (v >= '0' && v <= '9') {
                sum = sum * 10 + v - '0';
            } else {
                num.emplace_back(sum);
                op.emplace_back(v);
                sum = 0;
            }
        }
        num.emplace_back(sum);
    }
    REP (i, SZ(num)) {
        REP (j, SZ(num)) {
            mx[i][j] = -INF;
            mn[i][j] = INF;
        }
    }

    solve(0, SZ(num)-1);
    cout << mx[0][SZ(num)-1] << endl;
    return 0;
}
