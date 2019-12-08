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

const int MAXN = 5003;
const ll MOD = 1000000007;

int ans[MAXN][MAXN], sum[MAXN];
vector<int> pL[MAXN];

void build (const string &str) {
    int n = SZ(str);
    REP (i, n) {
        for (int j=0; i-j>=0&&i+j<n; j++) {
            if (str[i+j] == str[i-j]) {
                pL[i+j].emplace_back(i-j);
            } else {
                break;
            }
        }
    }
    REP (i, n) {
        for (int j=0; i-j>=0&&i+j+1<n; j++) {
            if (str[i+j+1] == str[i-j]) {
                pL[i+j+1].emplace_back(i-j);
            } else {
                break;
            }
        }
    }

    REP (i, n) {
        sort(pL[i].begin(), pL[i].end());
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    string str;
    cin >> str;

    build(str);

    int n = SZ(str);
    for (int r=n-1; r>=0; r--) {
        ans[r][r-1] = 0;

        REP (i, n) {
            while (SZ(pL[i]) && pL[i].back()>=r) {
                pL[i].pop_back();
                sum[i]++;
            }
        }
        pary(sum, sum+n);

        int cur = 0;
        for (int i=r; i<n; i++) {
            cur += sum[i];
            ans[r][i] = cur;
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--,r--;
        cout << ans[l][r] << endl;
    }
}
