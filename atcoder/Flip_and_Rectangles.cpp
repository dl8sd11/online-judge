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

const int MAXN = 2003;
const ll MOD = 1000000007;

int h, w, le[MAXN], re[MAXN], hei[MAXN];
bool org[MAXN][MAXN], tra[MAXN][MAXN], fin[MAXN][MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> h >> w;
    REP1 (i, h) {
        REP1 (j, w) {
            char c;
            cin >> c;
            org[i][j] = c == '#';
            tra[i][j] = org[i][j] ^ org[i-1][j];
            fin[i][j] = tra[i][j] ^ tra[i][j-1] ^ 1;
        }
    }

    REP1 (i, h) {
        fin[i][1] = 0;
    }
    REP1 (i, w) {
        fin[1][i] = 0;
    }

    int ans = max(h, w);
    REP1 (i, h) {
        REP1 (j, w + 1) {
            hei[j] = fin[i][j] ? hei[j] + 1 : 0;
        }
        vector<pair<int,int> > l, r;
        REP1 (j, w+1) {
            while (!l.empty() && l.back().second >= hei[j]) {
                l.pop_back();
            }
            if (l.size()) {
                le[j] = l.back().first;
            }
            l.emplace_back(j, hei[j]);
        }

        for (int j=w+1; j>=1; j--) {
            while (!r.empty() && r.back().second >= hei[j]) {
                r.pop_back();
            }
            if (r.size()) {
                re[j] = r.back().first;
            }
            r.emplace_back(j, hei[j]);
        }

        REP1 (j, w) {
            ans = max(ans, (hei[j]+1) * (re[j]-le[j]));
        }
    }

    cout << ans << endl;

    return 0;
}
