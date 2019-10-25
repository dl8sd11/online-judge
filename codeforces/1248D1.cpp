#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 502;
const ll MOD = 1000000007;

int n;
char c[MAXN];
int pre[MAXN], mn, lst, hd, tl;
pair<int,int> deq[MAXN*3];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        cin >>  c[i];
    }

    int mx = 0;
    pair<int,int> ans;

    bool nans = false;
    REP (i, n) {
        REP (j, n) {
            swap(c[i], c[j]);
            int cnt = 0, cur = 0, sum = 0;
            hd = 0, tl = 0;

            for (int k=0; k<n; k++) {
                cur = cur + (c[k] == '(' ? 1 : -1);
                while (tl-hd>0 && deq[tl-1].first >= cur) {
                    tl--;
                }
                deq[tl++] = {cur, k};
            }
            if (cur != 0) {
                nans = true;
            }

            for (int k=0; k<n; k++) {
                if (deq[hd].first + sum >= 0) {
                    cnt++;
                }
                if (deq[hd].second == k) {
                    hd++;
                }
                sum -= (c[k] == '(' ? 1 : -1);
                while (tl-hd>0 && deq[tl-1].first >= cur - sum) {
                    tl--;
                }
                deq[tl++] = {cur-sum, n + 3};
            }

            if (cnt >= mx) {
                mx = cnt;
                ans = {i, j};
            }
            swap(c[i], c[j]);
        }
    }

    cout << (nans ? 0 : mx) << endl;
    cout << ans.first+1 << " " << ans.second+1 << endl;
}
