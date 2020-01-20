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


const int MAXN = 1000005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, k, p;
vector<int> ban[MAXN];

bool valid (int ar[]) {
    for (int i=0;i<n;i++) {
        int c = ar[i];
        int x = ar[(i+1)%n];

        if (abs(c-x) > p) {
            return false;
        }

        for (auto v : ban[c]) {
            if (v == x) {
                return false;
            }
        }
    }
    return true;
}

namespace nle5 {
    int perm[5];
    int solve () {
        perm[0] = n;
        int ans = 0;
        for (int i=1;i<n;i++) {
            perm[i] = i;
        }
        do {
            ans += valid(perm);
            #ifdef tmd

            if (valid(perm)) {
                pary(perm,perm+n);
            }

            #endif // tmd
        } while (next_permutation(perm+1,perm+n));
        return ans;
    }
}

namespace pe2 {
    int ans[MAXN];
    int solve () {
        int cur = n, dl = -2;
        int res = 0;
        for (int i=0;i<n;i++) {
            if (cur <= 0) {
                dl *= -1;
                if (n&1) {
                    cur = 2;
                } else {
                    cur = 1;
                }
            }
            ans[i] = cur;
            cur += dl;
        }
        pary(ans,ans+n);

        res += valid(ans);
        reverse(ans+1,ans+n);
        res += valid(ans);

        return res;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k >> p;
    for (int i=0;i<k;i++) {
        int l, r;
        cin >> l >> r;
        ban[l].emplace_back(r);
    }

    if (p == 0) {
        cout << (n==1?1:0) << endl;
    } else if (p == 1) {
        cout << (n<=2&&k==0?1:0) << endl;
    } else if (n <= 5) {
        cout << nle5::solve() << endl;
    } else {
        cout << pe2::solve() << endl;
    }

}
