#include <bits/stdc++.h>
#include "lib1739.h"
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

const int MAXN = 300005;
const int MAXLG = __lg(MAXN) + 3;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;


int lc[MAXN*MAXLG*2], rc[MAXN*MAXLG*2], val[MAXN*MAXLG*2];

int n, m;
int pos[MAXN];
int id[MAXN];

int cnt;
int getNew(int from) {
    lc[cnt] = lc[from];
    rc[cnt] = rc[from];
    val[cnt] = val[from];
    return cnt++;
}

int getNew (int l, int r, int v) {
    lc[cnt] = l;
    rc[cnt] = r;
    val[cnt] = v;
    return cnt++;
}

int build(int l, int r) {
    if (r == l + 1) {
        return getNew(0,0,l);
    } else {
        int mid = (l + r) >> 1;
        return getNew(build(l,mid),build(mid,r),0);
    }
}

int chg (int p, int v, int id, int l=1, int r=n+1) {
    int ret = getNew(id);
    if (l == p && r == p+1) {
        val[ret] = v;
    } else {
        int mid = (l + r) >> 1;
        if (p >= mid) {
            rc[ret] = chg(p, v, rc[ret], mid, r);
        } else {
            lc[ret] = chg(p, v, lc[ret], l, mid);
        }
    }
    return ret;
}

int qry (int p, int nd, int l=1, int r=n+1) {
    if (l == p && r == p+1) {
        return val[nd];
    } else {
        int mid = (l + r) >> 1;
        if (p >= mid) {
            return qry(p, rc[nd], mid, r);
        } else {
            return qry(p, lc[nd], l, mid);
        }
    }
}

/*********************GoodLuck***********************/
int main () {
    scanf("%d %d",&n,&m);

    pos[0] = build(1, n+1);
    REP1 (i, n) {
        id[i] = i;
    }

    REP1 (i, m) {
        int p;
        scanf("%d",&p);

        int idL = id[p];
        int idR = id[p+1];

        int posL = qry(idL, pos[i-1]);
        int posR = qry(idR, pos[i-1]);

        swap(id[p], id[p+1]);

        pos[i] = chg(idL, posR, pos[i-1]);
        pos[i] = chg(idR, posL, pos[i]);
    }


    int A, B;

    int q = getNumQuestions();

    while (q--) {
        getQuestion(A, B);
        answer(qry(A, pos[B]));
    }
}
