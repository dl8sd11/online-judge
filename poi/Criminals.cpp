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

int n, k, c[MAXN], m, l;
int x[MAXN], y[MAXN], dx[MAXN], dy[MAXN], lst[MAXN];
int ix[MAXN], iy[MAXN], mx[MAXN], r[MAXN];

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP1 (i, n) {
        cin >> c[i];
        mx[c[i]] = i;
    }

    cin >> m >> l;
    REP1 (i, m) {
        cin >> x[i];
        ix[x[i]] = i;
    }
    REP1 (i, l) {
        cin >> y[i];
        iy[y[i]] = i;
    }

    REP1 (i, n) {
        if (ix[c[i]]) {
            if (ix[c[i]] == 1) {
                lst[1] = i;
            } else {
                lst[ix[c[i]]] = lst[ix[c[i]]-1];
            }
        }
        dx[i] = lst[m];
    }

    fill(lst, lst+MAXN, n+1);
    for (int i=n; i>=1; i--) {
       if (iy[c[i]]) {
            if (iy[c[i]] == 1) {
                lst[1] = i;
            } else {
                lst[iy[c[i]]] = lst[iy[c[i]]-1];
            }
        }
        dy[i] = lst[l];
    }

    pary(dx+1, dx+1+n);
    pary(dy+1, dy+1+n);

    int cur = 0;
    REP1 (i, n) {
        cur = max(cur, mx[c[i]]);
        r[i] = cur;
    }
    vector<int> ans;
    REP1 (i, n) {
        if (c[i] == x[m] && dx[i] > 1 && dy[i] < r[dx[i]-1]) {
            debug(dx[i], dy[i]);
            ans.emplace_back(i);
        }
    }

    cout << SZ(ans) << endl;
    if (ans.empty()) {
        cout << endl;
    } else {
        REP (i, SZ(ans)) {
            cout << ans[i] << " \n"[i==SZ(ans)-1];
        }
    }

}

/*

*/
