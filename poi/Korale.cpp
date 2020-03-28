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
template<typename T> ostream &operator << (ostream &os,const vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T,typename S> ostream &operator << (ostream &os,pair<T,S> &v){return os<<"{"<<v.X<<","<<v.Y<<"}";}
//template<typename T,typename S> ostream &operator << (ostream &os,map<T,S> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1000005;
const ll MOD = 1000000007;
const int MAXLG = __lg(MAXN) + 3;

int n, k;
vector<int> a;
vector<pair<int,int> > sa;
int mn[MAXLG][MAXN];

void build_table () {
    REP (i, n) {
        mn[0][i] = a[i];
    }
    REP1 (i, MAXLG-1) {
        REP (j, n) {
            if (j + (1<<i) <= n) {
                mn[i][j] = min(mn[i-1][j], mn[i-1][j+(1<<i-1)]);
            }
        }
    }
}

int qry (int l, int r) {
    int len = __lg(r-l);
    return min(mn[len][l], mn[len][r-(1<<len)]);
}

void dfs (int lst, ll sum, int &cnt, ll lim) {
    if (sum <= lim) {
        cnt++;
    }
    for (int i=lst; i<n; i++) {
        if (sum+sa[i].X>lim || cnt >= k) {
            break;
        }
        dfs(i+1, sum+sa[i].X, cnt, lim);
    }
}


vector<int> cur, res;

int tot;
void gen (int lst, ll sum, ll lim) {
    if (sum == lim) {
        debug(lst, cur, sum);
        tot++;
        if (tot == k) {
            res = cur;
            return;
        }
    }

    for (int i=lst;i<n; ) {
        if (qry(i,n) + sum > lim || tot >= k) {
            break;
        }

        int l = i-1, r = n-1;
        while (l < r - 1) {
            int m = (l + r) >> 1;
            if (qry(i, m+1) + sum > lim) {
                l = m;
            } else {
                r = m;
            }
        }

        cur.eb(r);
        gen(r+1, sum+a[r], lim);
        cur.pop_back();

        i = r+1;
    }
}
/*
4 10
3 7 4 3

*/

ll kth_value () {
    ll L = -1, R = 1000000000000015LL;
    while (L < R - 1) {
        ll M = (L + R) >> 1;
        int sz = 0;
        dfs(0, 0, sz, M);
        if (sz < k) {
            L = M;
        } else {
            R = M;
        }
    }
    return R;
}

/*********************GoodLuck***********************/
int main () {
    IOS();


    cin >> n >> k;
    sa.resize(n);
    a.resize(n);
    REP (i, n) {
        cin >> sa[i].X;
        a[i] = sa[i].X;
        sa[i].Y = i + 1;
    }

    sort(ALL(sa));

    ll val = kth_value();
    cout << val << endl;


    build_table();

    int dl = 0;
    dfs(0, 0, dl, val-1);
    k -= dl;

    gen(0, 0, val);
    debug(res);

    int sz = SZ(res);
    REP (i, sz) {
        cout << res[i]+1 << " \n"[i==sz-1];
    }



    #ifdef tmd
    for (k=1; k<=16; k++) {
        cout << kth_value() << endl;
    }
    #endif
}
/*
4 1
3 4 7 3
*/
