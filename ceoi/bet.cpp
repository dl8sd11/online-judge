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

int n;
double a[MAXN], b[MAXN];

int ai, bi;
double asum, bsum, cnt, ans;

void upd () {
    ans = max(ans, min(asum-cnt, bsum-cnt));
}

void addA () {
    asum += a[ai];
    ai++;
    cnt++;
}

void addB () {
    bsum += b[bi];
    bi++;
    cnt++;
}
/*********************GoodLuck***********************/
int main () {

    scanf("%d",&n);
    REP (i, n) {
        scanf("%lf %lf", a+i, b+i);
    }

    sort(a,a+n);
    sort(b,b+n);
    reverse(a,a+n);
    reverse(b,b+n);


    while (ai<n || bi<n) {
        if (ai == n) {
            addB();
        } else if (bi == n) {
            addA();
        } else {
            if (asum < bsum) {
                addA();
            } else {
                addB();
            }
        }
        upd();
        debug(asum, bsum, ai, bi);
    }

    printf("%.4lf",ans);
}
