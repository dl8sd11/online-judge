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

const int MAXN = 102;
const ll MOD = 1000000007;


int t, r, c, k;
bool rice[MAXN][MAXN];
char chick[62], ans[MAXN][MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    REP (i, 26) {
        chick[i] = 'a' + i;
        chick[i+26] = 'A' + i;
    }
    REP (i, 10) {
        chick[i+52] = '0' + i;
    }

    cin >> t;
    while (t--) {
        cin >> r >> c >> k;

        int rcnt = 0;
        REP (i, r) {
            REP (j, c) {
                char ch;
                cin >> ch;
                rice[i][j] = ch == 'R';
                rcnt += ch == 'R';
            }
        }
        vector<int> vec(k, rcnt / k);
        debug(k - rcnt/k*k);
        REP (i, rcnt - rcnt/k*k) {
            vec[i]++;
        }

        int idx = 0;
        for (int i=0; i<r; i++) {
            if (i&1) {
                for (int j=0; j<c; j++) {
                    if (vec.empty()) {
                        ans[i][j] = chick[k-1];
                    } else {
                        ans[i][j] = chick[idx];
                        if (rice[i][j]) {
                            vec.back()--;
                        }
                        if (vec.back() == 0) {
                            idx++;
                            vec.pop_back();
                        }
                    }
                }
            } else {
                for (int j=c-1; j>=0; j--) {
                    if (vec.empty()) {
                        ans[i][j] = chick[k-1];
                    } else {
                        ans[i][j] = chick[idx];
                        if (rice[i][j]) {
                            vec.back()--;
                        }
                        if (vec.back() == 0) {
                            idx++;
                            vec.pop_back();
                        }
                    }
                }
            }
        }

        REP (i, r) {
            REP (j, c) {
                cout << ans[i][j];
            }
            cout << endl;
        }
    }

}
