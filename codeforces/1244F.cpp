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

const int MAXN = 200005;
const ll MOD = 1000000007;

int n, k;
int id[MAXN];
bool w[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP (i, n) {
        char c;
        cin >> c;
        w[i] = c == 'W';
    }

    int bs = -1;
    REP (i, n) {
        if (w[i] == w[(i+1)%n]) {
            bs = i;
        }
    }

    if (bs == -1) {
        REP (i, n) {
            cout << (w[i]^(k&1) ? 'W' : 'B');
        }
        cout << endl;
    } else {
        REP (i, n) {
            id[i] = (bs + 1 + i) % n;
            debug(id[i]);
        }
        int lst = 0;
        for (int i=1; i<n-1; i++) {
            int p = id[i-1], f = id[i+1], ff = id[(i+2)%n], c = id[i];
            if (w[p] != w[c] && w[c] != w[f]) {
                if (w[f] == w[ff]) {
                    debug(lst, i);
                    int gap = (i-lst)/2;
                    if (w[id[lst]] == w[id[i+1]]) {
                        gap++;
                    }
                    int len = min(gap, k);
                    REP1 (j, len) {
                        w[id[lst+j]] = w[id[lst]];
                        w[id[i-j+1]] = w[id[i+1]];
                    }
                    for (int j=lst+len+1; j<=i-len; j++) {
                        w[id[j]] ^= (k&1);
                    }
                }
            } else {
                lst = i;
            }
        }

        REP (i, n) {
            cout << (w[i] ? 'W' : 'B');
        }
        cout << endl;
    }


    return 0;
}
