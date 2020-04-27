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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int n;
string s1, s2;
int dpre[MAXN], dp[MAXN];

int sum (int l, int r) {
    return dpre[r] - dpre[l-1];
}
/*********************GoodLuck***********************/
int main () {
    IOS();


    cin >> n;

    cin >> s1 >> s2;

    for (int i=0; i<n; i++) {
        dpre[i+1] = dpre[i] + (s1[i] != s2[i]);
    }

    for (int i=1; i<=n; i++) {
        dp[i] = i;
        for (int j=0; j<i; j++) {
            dp[i] = min(dp[i], dp[j] + min(sum(j+1, i), 1+(i-j)-sum(j+1,i)));
        }
    }

    pary(dp, dp+n+1);
    pary(dpre, dpre+n+1);
    cout << dp[n] << endl;
}

