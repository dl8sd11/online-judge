#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
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

const int MAXN = 1000005;
const ll MOD = 1000000007;
ld EPS = 1e-10;


pdd line[MAXN];
int tr[MAXN];
int sz;

ld ins (const pdd &p1, const pdd &p2) {
    return (p2.Y-p1.Y) / (p1.X - p2.X);
}

void add_line (ld a, ld b, int id) {
    pdd nw = {a, b};
    while (sz >= 2 && ins(line[sz-1], line[sz-2]) >= ins(line[sz-2], nw)) {
        sz--;
    }
    tr[sz] = id;
    line[sz++] = nw;
}

int frm;
ld eval (ld x) {
    int l = -1, r = sz-1;
    while (l < r - 1) {
        int m = (l + r) >> 1;
        if (ins(line[m], line[m+1]) >= x) {
            r = m;
        } else {
            l = m;
        }
    }

    frm = tr[r];
    return line[r].X * x + line[r].Y;
}

int n;
ld a[MAXN], p[MAXN], dp[MAXN], ans[MAXN], src[MAXN];
/*********************GoodLuck***********************/
int main () {

    scanf("%d", &n);
    for (int i=n; i>=1; i--) {
        int x;

        #ifdef tmdd
        x = i == n ? 2 : 1;
        #else
        scanf("%d", &x);
        #endif
        a[i] = x;

    }



    ld sum = 0;
    add_line(0, 0, 0);

    ld mx = 0;
    for (int i=1; i<=n; i++) {
        sum += a[i];
        mx = max(mx, a[i]);

        p[i] = sum;
        ld l = 0, r = mx + 1;
        while (r-l >= EPS/10) {
            ld x = (l + r) / 2;
//            debug(i, x, eval(-x), p[i]-x*i);
            if (eval(-x) >= p[i]-x*i) {
                r = x;
            } else {
                l = x;
            }
        }
        dp[i] = r;

        eval(-r);
        src[i] = frm;
//        debug(i, r, eval(-4));
        add_line(i, p[i], i);
    }

    for (int i=n,j; i>=1; i=j) {
        j = src[i];

        for (int k=j+1; k<=i; k++) {
            printf("%.9f\n",(double)dp[i]);
        }
//        debug(i, j);
    }



}
