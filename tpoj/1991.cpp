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

const int MAXN = 2200006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int r, c, q;
bool g[MAXN];
int prer[MAXN],prec[MAXN];

int toId (int x, int y) {
    return x * (c + 1) + y;
}

int getSum(int *pre,int r1, int c1, int r2, int c2) {
    if (r1 > r2 || c1 > c2) {
        return 0;
    }
    return pre[toId(r2,c2)] - \
            pre[toId(r2,c1-1)] - pre[toId(r1-1,c2)] \
            + pre[toId(r1-1,c1-1)];
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> r >> c;
    REP1 (i, r) {
        REP1 (j, c) {
            char ch;
            cin >> ch;
            g[toId(i,j)] = ch == '1';
            if (ch == '1' && g[toId(i-1,j)]) {
                prer[toId(i-1,j)]++;
            }
            if (ch == '1' && g[toId(i,j-1)]) {
                prec[toId(i,j-1)]++;
            }
        }
    }


    REP1 (i, r) {
        REP1 (j, c) {
            prer[toId(i,j)] += prer[toId(i,j-1)] + prer[toId(i-1,j)] - prer[toId(i-1,j-1)];
            prec[toId(i,j)] += prec[toId(i,j-1)] + prec[toId(i-1,j)] - prec[toId(i-1,j-1)];
        }
    }

    REP1 (i, r) {
        REP1 (j, c) {
            #ifdef tmd
            cout << prer[toId(i,j)] << " \n"[j==c];
            #endif
        }
    }

    cin >> q;
    while (q--) {
        int r1, r2, c1, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        int rans = getSum(prer,r1, c1, r2-1, c2);
        int cans = getSum(prec, r1,c1, r2, c2-1);
        cout << rans + cans << endl;
    }
}
