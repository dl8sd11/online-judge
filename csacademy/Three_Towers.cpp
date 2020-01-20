/*
I think this is a case heavy problem, so I decided not to implement right now.

Solution
for every [i..n] check the shortest decreasement of right endpoint to make valid range.

So the distribution of [i..n] have these cases:
H: high, L:low, M: medium

HML
 - base case, valid itself
MMM
 - can solve by dp with groups of length 3
HHL
 - H-L == 1
    - n != L
      case HLL
    - n == L
     - case below
 - H-L > 1
    - the rightest H (any of the two)
HLL
 - reduce to MMM or valid
*/

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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int n;
string str;
int a[MAXN];
int pre[MAXN][3], dp[MAXN], lst[MAXN];

int dif (int idx) {
    bool vis[3] = {};
    REP (i, 3) {
        vis[a[i]] = true;
    }
    int cnt = 0;
    REP (i, 3) {
        cnt += vis[i];
    }
    return cnt;
}

void build () {
    REP1 (i, n) {
        REP (j, 3) {
            pre[i][j] = pre[i-1][j];
        }
        pre[i][a[i]]++;
    }

    a[0] = -1;
    REP1 (i, n) {
        if (a[i] != a[i-1]) {
            lst[i] = i;
        } else {
            lst[i] = lst[i-1];
        }
    }

    dp[1] = dp[2] = -1;
    for (int i=3; i<=n; i++) {
        int d = dif(i);
        if (d == 3) {
            dp[i] = dp[i-3];
        } else if (d == 2) {
            dp[i] = i-2;
        } else {
            dp[i] = lst[i];
        }
    }
}

int rng (int l, int r, int k) {
    return pre[r][k] - pre[l-1][k];
}
/*********************GoodLuck***********************/

// first two idx

int main () {
    IOS();

    cin >> n >> str;
    REP1 (i, n) {
        a[i] = str[i-1];
    }

    int ans = 0;
    REP1 (i, n) {
        for (int j=n;j>=i;j++) {
            int s[3];
            REP (k, 3) {
                s[j] = rng(i, j, k);
            }
            if (s[0] != s[1] && s[1] != s[2] && s[0] != s[2]) {
                ans = max(ans, j-i+1);
                break;
            } else {

            }
        }
    }

    assert(ans > 0);
}
