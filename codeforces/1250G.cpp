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

const int MAXN = 200005;
const ll MOD = 1000000007;

int t, n, k, a[MAXN], b[MAXN];

ll dp[MAXN], tr[MAXN], he[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n >> k;

        REP1 (i, n) {
            cin >> a[i];
        }

        REP1 (i, n) {
            cin >> b[i];
        }

        dp[0] = he[0] = 0;
        tr[0] = -1;

        int bst = -1, mstep = MOD;

        int hd = 0;
        ll h1 = 0, h2 = 0;

        deque<int> rmq = {0};

        REP1 (i, n) {
            h1 += a[i], h2 += b[i];
            he[i] = min(h1, h2);

            while (hd < i && max(h1, h2)-he[hd] >= k) {
                if (h1-he[hd] < k && h2 - he[hd] >= k) {
                    // win
                    if (dp[hd] < mstep) {
                        mstep = dp[hd];
                        bst = hd;
                    }
                }
                if (rmq.front() == hd) {
                    rmq.pop_front();
                }
                hd++;
            }

            if (hd == i) {
                break;
            }

            assert(rmq.size() >= 1);
            tr[i] = rmq.front();
            dp[i] = dp[tr[i]] + 1;

            while (dp[i] <= dp[rmq.back()]) {
                rmq.pop_back();
            }
            rmq.eb(i);
        }

//        debug(bst, mstep);

        if (mstep == MOD) {
            cout << -1 << endl;
        } else {
            cout << mstep << endl;

            vector<int> ans;
            while (bst != 0) {
                ans.eb(bst);
                bst = tr[bst];
            }
            reverse(ALL(ans));

            REP (i, SZ(ans)) {
                cout << ans[i];
                if (i != SZ(ans)-1) {
                    cout << " ";
                }
            }

            cout << endl;
        }
    }
}
