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

const int MAXN = 50004;
const int MAXQ = 200005;
const int MAXK = 21;
const ll MOD = 1000000007;

int n, k, q, a[MAXN];
pii rng[MAXQ];
int ans[MAXQ];

void add (int &x, int y) {
    x = x + y >= MOD ? x + y - MOD : x + y;
}

int dp[MAXN][MAXK];
int ed[MAXK];

void buildL (int l, int r) {
    for (int st=1;st<=k;st++) {
        for (int i=1;i<=k; i++) {
            ed[i] = 0;
        }
        for (int i=r; i>=l; i--) {
            int sum = 0;

            if (a[i] <= st) {
                for (int j=st;j>=a[i];j--) {
                    add(sum, ed[j]);
                }
                add(ed[a[i]], sum+(st==a[i]));
            }

            sum = 0;
            for (int j=st;j>=1;j--) {
                add(sum, ed[j]);
            }
            dp[i][st] = sum;
        }
    }
}

void buildR (int l, int r) {
    for (int st=1;st<=k;st++) {
        for (int i=1;i<=k; i++) {
            ed[i] = 0;
        }
        for (int i=l; i<=r; i++) {
            int sum = 0;

            if (a[i] >= st) {
                for (int j=st;j<=a[i];j++) {
                    add(sum, ed[j]);
                }
                add(ed[a[i]], sum+1);
            }

            sum = 0;
            for (int j=st;j<=k;j++) {
                add(sum, ed[j]);
            }
            dp[i][st] = sum;
        }
    }
}

int mrg (int l, int r, int m) {

    int res = 0;
    for (int i=1;i<=k; i++) {
//        debug(i, dp[l][i], dp[r][i]);
        add(res, 1LL*dp[l][i]*dp[r][i]%MOD);
    }

//    debug(dp[l][k]);
//    debug(dp[r][1]);

    for (int i=1; i<=k; i++) {
        add(res, dp[l][i]);
    }
    add(res, dp[r][1]);

    return res;
}

void solve (int l, int r, vector<int> qid) {
    if (l == r) {
        for (auto v : qid) {
            ans[v] = 1;
        }
        return;
    }

    vector<int> qL, qR;
    int m = (l + r) >> 1;

    buildL(l,m);
    buildR(m+1,r);
    for (auto v : qid) {
        if (rng[v].Y <= m) {
            qL.eb(v);
        } else if (rng[v].X > m) {
            qR.eb(v);
        } else {
//            debug(v, l, m, r);
            ans[v] = mrg(rng[v].X,rng[v].Y,m);
        }
    }

    if (qL.size()) {
        solve(l, m, qL);
    }
    if (qR.size()) {
        solve(m+1,r,qR);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    #ifndef tmd
    freopen("nondec.in","r",stdin);
    freopen("nondec.out","w",stdout);
    #endif // tmd

    cin >> n >> k;
    REP1 (i, n) {
        #ifdef tmd
        a[i] = rand() % k + 1;
        #else
        cin >> a[i];
        #endif // tmd
    }

    cin >> q;

    vector<int> qid;
    REP (i, q) {
        #ifdef tmd
        rng[i].X = rand() % n + 1;
        rng[i].Y = rand() % n + 1;
        if (rng[i].X > rng[i].Y) {
            swap(rng[i].X, rng[i].Y);
        }
        #else
        cin >> rng[i].X >> rng[i].Y;
        #endif // tmd
        qid.emplace_back(i);
    }

    solve(1, n, qid);
    for (int i=0;i<q;i++) {
        cout << ans[i]+1 << endl;
    }
}

/*
10 5
1 2 3 4 5 2 3 4 5 1
1
1 1

*/
