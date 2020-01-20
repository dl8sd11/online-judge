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
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, plim, mlim;
int k, b, sum;

int kid[MAXN];
vector<int> kgp[MAXN];

// 6 100000 100000
vector<int> edg[500000];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> mlim >> plim;
    b = 3;
    k = max(1,int(n/sqrt(mlim - 2*n*b)+1));
    debug(n, k, b);

    int cnt = 0;
    int kcnt = 0;
    for (int i=1;i<=n;i++) {
        kid[i] = kcnt;
        cnt++;
        if (i==n || cnt == k) {
            kcnt++;
            cnt = 0;
        }
    }
    int khf = kcnt;

    for (int i=1+n;i<=n+n;i++) {
        kid[i] = kcnt;
        cnt++;
        if (i==n+n || cnt == k) {
            kcnt++;
            cnt = 0;
        }
    }

    int bid = n*2+1;
    REP (i, kcnt) {
        REP (j, b) {
            kgp[i].emplace_back(bid++);
        }
    }

    REP1 (i, n*2) {
        for (auto v : kgp[kid[i]]) {
            if (i > n) {
                edg[v].emplace_back(i);
                sum++;
            } else {
                edg[i].emplace_back(v);
                sum++;
            }
        }
    }

    int sz = (kcnt - khf + b - 1) / b;
    REP (i, khf) {
        for (int j=khf;j<kcnt;j++) {
            edg[kgp[i][(j-khf)/sz]].emplace_back(kgp[j][i/sz]);
            sum++;
        }
    }

    cout << bid - 1 << " " << sum << endl;

    int nsum = 0;
    REP1 (i, bid-1) {
        for (auto v : edg[i]) {
            cout << i << " " << v << endl;
            nsum++;
        }
    }

    assert(nsum == sum);
}
