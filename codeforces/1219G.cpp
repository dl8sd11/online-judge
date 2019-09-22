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

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, m;
int a[MAXN];
ll rsum[MAXN], csum[MAXN];
int &aa (int x, int y) {
    return a[x * m + y];
}
ll ans = 0, cur, sum;
void check04 () {
    vector<ll> rs, cs;
    REP (i, n) {
        sum = 0;
        REP (j, m) {
            sum += aa(i, j);
        }
        rs.emplace_back(sum);
        rsum[i] = sum;
    }
    sort(rs.begin(), rs.end());
    cur = 0;
    REP1 (i, min(4, SZ(rs))) {
        cur += rs[SZ(rs)-i];
    }
    ans = max(ans, cur);

    REP (j, m) {
        sum = 0;
        REP (i, n) {
            sum += aa(i, j);
        }
        cs.emplace_back(sum);
        csum[j] = sum;
    }
    sort(cs.begin(), cs.end());
    cur = 0;
    REP1 (i, min(4, SZ(cs))) {
        cur += cs[SZ(cs)-i];
    }
    ans = max(ans, cur);
}

void check13 () {
    REP (k, n) {
        cur = 0;
        vector<ll> cs;
        REP (j, m) {
            sum = 0;
            cs.emplace_back(csum[j] - aa(k, j));
            cur += aa(k, j);
        }
        sort(cs.begin(), cs.end());
        REP1 (i, min(3, SZ(cs))) {
            cur += cs[SZ(cs)-i];
        }
        ans = max(ans, cur);
    }

    REP (k, m) {
        cur = 0;
        vector<ll> cs;
        REP (i, n) {
            sum = 0;
            cs.emplace_back(rsum[i] - aa(i, k));
            cur += aa(i, k);
        }
        sort(cs.begin(), cs.end());
        REP1 (i, min(3, SZ(cs))) {
            cur += cs[SZ(cs)-i];
        }
        ans = max(ans, cur);
    }
}

void check22 () {
    if (n < m) {
        REP (x, n) {
            REP (y, n) {
                if (x == y) {
                    continue;
                }
                cur = 0;
                pair<ll,ll> mx;
                REP (j, m) {
                    ll tmp = csum[j] - aa(x, j) - aa(y, j);
                    if (tmp > mx.first)  {
                        mx.second = mx.first;
                        mx.first = tmp;
                    } else if (tmp > mx.second){
                        mx.second = tmp;
                    }
                    cur += aa(x, j) + aa(y, j);
                }
                ans = max(ans, cur + mx.first + mx.second);

            }
        }
    } else {
        REP (x, m) {
            REP (y, m) {
                if (x == y) {
                    continue;
                }
                cur = 0;
                pair<ll,ll> mx;
                REP (i, n) {
                    ll tmp = rsum[i] - aa(i, x) - aa(i, y);
                    if (tmp > mx.first)  {
                        mx.second = mx.first;
                        mx.first = tmp;
                    } else if (tmp > mx.second){
                        mx.second = tmp;
                    }
                    cur += aa(i, x) + aa(i, y);
                }
                ans = max(ans, cur + mx.first + mx.second);
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> m;
    REP (i, n) {
        REP (j, m) {
            cin >> aa(i, j);
        }
    }

    check04();
    debug(ans);
    check13();
    debug(ans);
    check22();
    debug(ans);

    cout << ans << endl;

    return 0;
}
