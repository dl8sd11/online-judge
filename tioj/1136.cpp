#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MEM(a,b) memset(a,b,sizeof(a))
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

const int MAXN = 102;
const ll MOD = 1000000007;

struct Matrix {
    double dt[MAXN][MAXN];

    Matrix () {
        MEM(dt, 0);
    }

    Matrix operator* (const Matrix &oth) const {
        Matrix ret;
        REP (i, MAXN) {
            REP (j, MAXN) {
                REP (k, MAXN) {
                    ret.dt[i][j] += dt[i][k] * oth.dt[k][j];
                }
            }
        }
        return ret;
    }
};

int n, t, c;
int cnt[MAXN];

Matrix mpow (Matrix bs, int pw) {
    if (pw == 1) {
        return bs;
    }
    Matrix ret = mpow(bs, pw>>1);
    return (pw % 2 == 1) ? ret * ret * bs : ret * ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    while (cin >> n >> t && (n + t)) {
        cin >> c;
        Matrix bs, init;

        MEM(cnt, 0);
        REP (i, c) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            bs.dt[u][v] = 1;
            bs.dt[v][u] = 1;
            cnt[u]++;
            cnt[v]++;
        }

        REP (j, n) {
            init.dt[j][0] = 1.0 / n;
            if (cnt[j] == 0) {
                continue;
            }
            REP (i, n) {
                bs.dt[i][j] /= cnt[j];
            }
        }


        if (t == 0) {
            bs = init;
        } else {
            bs = mpow(bs, t) * init;
        }

        int x;
        cin >> x;

        cout << fixed << setprecision(4) << bs.dt[x-1][0] << endl;
    }
}
