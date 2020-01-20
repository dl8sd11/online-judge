#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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
const int MAXC = 26;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;



/*
Solution
Divide and Conquer


the solve [l..r] we can greedily match l with j
s.t. s[l]==s[j] and both [l..j], [j+1..r] are valid

if we can find the match point in O(1)
we can solve the problem in O(n)

maintain dp[R][C] meaning greatest L s.t.
L <= R and S[L]==C and [L+1..R] is valid
*/
string str;
int dp[MAXN][MAXC];

void build () {
    memset(dp, -1, sizeof(dp));
    dp[0][str[0]-'a'] = 0;
    for (int i=1; i<SZ(str); i++) {
        dp[i][str[i]-'a'] = i;
        int lst = dp[i-1][str[i]-'a'];
        if (lst > 0) {
            for (int j=0;j<MAXC;j++) {
                dp[i][j] = max(dp[i][j], dp[lst-1][j]);
            }
        }
    }
}

char ans[MAXN];
void solve (int l, int r) {
    if (l < r) {
        int mp = dp[r][str[l]-'a'];
        if (mp <= l) {
            cout << -1 << endl;
            exit(0);
        }
        ans[l] = '(';
        ans[mp] = ')';

        solve(l+1, mp-1);
        solve(mp+1, r);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> str;
    build();
    solve(0, SZ(str)-1);

    for (int i=0;i<SZ(str);i++) {
        cout << ans[i];
    }
    cout << endl;
}
