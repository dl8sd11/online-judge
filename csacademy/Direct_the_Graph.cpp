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
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 2003;
const ll MOD = 1000000007;

int n;

int id[MAXN][MAXN];
int in[MAXN], out[MAXN];

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    int cnt = 0;
    REP1 (l, n) {
        for (int r=l+1; r<=n; r++) {
            id[l][r] = cnt++;
        }
    }

    vector<int> ans(cnt);

    for (int i=2; i<=n; i+=2) {
        for (int j=1; j+i<=n; j++) {
            bool rev = j & 1;
            ans[id[i-1][i+j]] = rev;
            ans[id[i][i+j]] = !rev;
            in[i+j]++, out[i+j]++;
            if (rev) {
                out[i-1]++;
                in[i]++;
            } else {
                in[i-1]++;
                out[i]++;
            }
        }
        ans[id[i-1][i]] = 0;
        in[i-1]++;
        out[i]++;
    }

    pary(in+1, in+1+n);
    pary(out+1, out+1+n);

    ll sum = 1LL * n * (n-1) * (n-2) / 6;
    ll no = 0;

    REP1 (i, n) {
        no += in[i]*(in[i]-1)/2;
        no += out[i]*(out[i]-1)/2;
    }
    no /= 2;
    debug(sum, no);

    cout << sum - no << endl;
    REP (i, SZ(ans)) {
        cout << ans[i];
    }
    cout << endl;

}
