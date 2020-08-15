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

const int MAXN = 100005;
const ll MOD = 1000000007;

int t;

void pre (vector<int> &vec,int k) {
    for (auto &v : vec) {
        if (v < k) {
            v = -1;
        } else if (v == k) {
            v = 0;
        } else {
            v = 1;
        }
    }
}

bool solve (const vector<int> &vec) {
    int lst = -MOD;
    if (vec.size() == 1) {
        return true;
    }
    for (int i=0; i<SZ(vec);i++) {
        if (vec[i] >= 0) {
            if (i - lst <= 2) {
                return true;
            }
            lst = i;
        }
    }
    return false;
}

bool zero (vector<int> vec) {
    for (auto v : vec) {
        if (v == 0) {
            return true;
        }
    }
    return false;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);

        for (int i=0;i<n;i++) {
            cin >> a[i];
        }

        pre(a, k);
        debug(a);

        cout << (solve(a) && zero(a) ? "yes" : "no") << endl;
    }


}

