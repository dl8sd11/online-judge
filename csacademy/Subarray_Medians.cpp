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


const int MAXN = 10004;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, a[MAXN], p[MAXN];
ll ans;

int fw[MAXN], bw[MAXN], hd, ed, med;
void build (int l, int r) {

    hd = ed = -1;
    for (int i=1;i<=n;i++) {
        if (p[i] >= l && p[i] <= r) {
            if (hd == -1) {
                hd = ed = p[i];
                fw[p[i]] = bw[p[i]] = -1;
            } else {
                fw[ed] = p[i];
                bw[p[i]] = ed;
                ed = p[i];
                fw[p[i]] = -1;
            }
        }

    }

    med = hd;
    REP (i, (r-l+1)/2) {
        med = fw[med];
    }

}

void rmv (int idx) {
    int f = fw[idx], b = bw[idx];

    if (b>=0) {
        fw[b] = f;
    } else {
        hd = f;
    }
    if (f>=0) {
        bw[f] = b;
    } else {
        ed = b;
    }

}

// #define test
int perm[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    srand(2443);
    cin >> n;
    REP (i ,n) {
        perm[i] = i+1;
    }
    random_shuffle(perm,perm+n);

    REP (i, n) {

        #ifdef test
        a[i] = perm[i];
        #else
        cin >> a[i];
        #endif // test
        p[a[i]] = i;
    }
    // pary(a,a+n);

    REP (i, n) {
        int R = (n-i)&1?n-1:n-2;
        build(i, R);

        ans += 1LL*(i+1)*(i+1)*a[i];
        for (int j=R;j>i;j-=2) {
            ans += 1LL*(i+1)*(j+1)*(a[med]);
            int cntl = 0, cntr = 0;


            if (a[j] > a[med]) {
                cntr++;
            } else if (a[j] < a[med]) {
                cntl++;
            }
            if (a[j-1] > a[med]) {
                cntr++;
            } else if (a[j-1] < a[med]) {
                cntl++;
            }

            if (cntl > cntr) {
                med = fw[med];
            } else if (cntl < cntr) {
                med = bw[med];
            }


            rmv(j);
            rmv(j-1);


        }
    }

    cout << ans << endl;

}
