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

const int MAXN = 102;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, a, b;
vector<int> ans;

void solve (int pos, int neg) {
    int lst = MOD;
    REP (i, n/pos) {
        REP (j, pos) {
            ans.emplace_back(n-i*pos-(pos-j-1));
            lst = min(lst, ans.back());
        }
    }

    int rem = neg - n/pos;
    debug(pos, neg, rem);
    for (int i=1;i<lst-rem;i++) {
        ans.emplace_back(i);
    }
    for (int i=lst-1;i>=lst-rem; i--) {
        ans.emplace_back(i);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> a >> b;

    if (n/a+1 <= b && n/a+n%a >= b) {
        solve(a, b);
    } else if (n/b+1 <= a && n/b+n%b >= a) {
        solve(b, a);
        reverse(ans.begin(), ans.end());
    } else {
        cout << -1 << endl;
        return 0;
    }

    debug(ans);


    if (ans.empty()) {
        cout << -1 << endl;
    } else {
#ifdef tmd
    int inc[MAXN], dd[MAXN];
    int imax = 0, dmax = 0;
    for (int i=0;i<n;i++) {
        inc[i] = dd[i] = 1;
        for (int j=0;j<i;j++) {
            if (ans[j]<ans[i]) {
                inc[i] = max(inc[i],inc[j] + 1);
            }
            if (ans[j] > ans[i]) {
                dd[i] = max(dd[i], dd[j]+1);
            }
        }
        imax = max(imax, inc[i]);
        dmax = max(dmax, dd[i]);
    }
    debug(imax, dmax);
    assert(imax == a && dmax == b);

#endif // tmd

        REP (i, SZ(ans)) {
            cout << ans[i] << " \n"[i==SZ(ans)-1];
        }

    }

}
/*
1 10
2 5
2 6
2 7
2 8
2 9
3 4
3 5
3 6
3 7
3 8
4 3
4 4
4 5
4 6
4 7
5 2
5 3
5 4
5 5
5 6
6 2
6 3
6 4
6 5
7 2
7 3
7 4
8 2
8 3
9 2
10 1

*/
