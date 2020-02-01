#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define MEM(a,b) memset(a,b,sizeof(a))
#define MN(a,b) a=min(a,b)
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

const int MAXN = 200005;
const int MAXLG = __lg(MAXN) + 3;
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;

int n;
pair<int,int> p[MAXN];
vector<int> val;
int r[MAXLG][MAXN];

int qry (int L, int R) {
    int ret = 0;
    for (int i=MAXLG-1;i>=0;i--) {
        if (r[i][L] <= R) {
            ret += 1<<i;
            L = r[i][L]+1;
        }
    }
    return ret;
}

set<int> rmv;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    val.reserve(n);
    REP (i, n) {
        cin >> p[i].first >> p[i].second;
        val.emplace_back(p[i].first);
    }
    sort(val.begin(),val.end());
    val.resize(unique(val.begin(),val.end())-val.begin());

    MEM(r, INF);
    REP (i, n) {
        p[i].first = lower_bound(val.begin(),val.end(),p[i].first)-val.begin();
        p[i].second = upper_bound(val.begin(),val.end(),p[i].second)-val.begin()-1;
        MN(r[0][p[i].first], p[i].second);
    }
    for (int i=SZ(val)-1;i>=0;i--) {
        MN(r[0][i], r[0][i+1]);
    }

    REP1 (i, MAXLG-1) {
        REP (j, SZ(val)) {
            if (r[i-1][j] < INF) {
                r[i][j] = r[i-1][r[i-1][j]+1];
            }
        }
    }

    rmv.insert(-1);
    rmv.insert(SZ(val));

    vector<int> ans;

    REP (i, n) {
        auto ptr = rmv.lower_bound(p[i].second);
        int L = *prev(ptr);
        int R = *ptr;

        if (L < p[i].first && p[i].second < R) {

            int LQ = qry(L+1, p[i].first-1);
            int RQ = qry(p[i].second+1, R-1);
            int bst = qry(L+1, R-1);

            if (LQ+RQ+1 == bst) {
                ans.emplace_back(i+1);

                for (int j=p[i].first;j<=p[i].second;j++) {
                    rmv.insert(j);
                }

            }
        }
    }

    cout << SZ(ans) << endl;
    REP (i, SZ(ans)) {
        cout << ans[i] << " \n"[i==SZ(ans)-1];
    }
}
