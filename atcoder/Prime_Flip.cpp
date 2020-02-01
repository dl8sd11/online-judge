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

const int MAXN = 202;
const int MAXC = 10000007;
const ll MOD = 1000000007;

int n, a[MAXN];
vector<int> b;
vector<int> odd, even;
vector<int> edg[MAXN];

bool sieve[MAXC];
vector<int> prime;
void build_prime () {
    sieve[1] = true;
    for (int i=2; i<MAXC; i++) {
        if (!sieve[i]) {
            prime.emplace_back(i);
        }
        for (int j=0; j<SZ(prime)&&i*prime[j]<MAXC; j++) {
            sieve[i*prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

bool vis[MAXN];
int yp[MAXN];

bool match (int nd) {
    if (vis[nd]) {
        return false;
    }
    vis[nd] = true;
    for (auto v : edg[nd]) {
        if (yp[v] == -1 || match(yp[v])) {
            yp[v] = nd;
            return true;
        }
    }
    return false;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    build_prime();

    cin >> n;
    REP1 (i, n) {
        cin >> a[i];
    }

    a[0] = -1;
    REP1 (i, n) {
        if (a[i] != a[i-1] + 1) {
            b.emplace_back(a[i]);
        }
        if (a[i] != a[i+1] - 1) {
            b.emplace_back(a[i]+1);
        }
    }

    for (auto v : b) {
        if (v & 1) {
            odd.emplace_back(v);
        } else {
            even.emplace_back(v);
        }
    }

    REP (i, SZ(odd)) {
        REP (j, SZ(even)) {
            if (!sieve[abs(odd[i] - even[j])]) {
                edg[i].emplace_back(j);
            }
        }
    }

    memset(yp, -1, sizeof(yp));

    int cnt = 0;
    REP (i, SZ(odd)) {
        memset(vis, 0, sizeof(vis));
        if (match(i)) {
            cnt++;
        }
    }

    cout << cnt + ((SZ(odd)-cnt)/2 + (SZ(even)-cnt)/2)*2 + (SZ(odd)-cnt)%2*3 << endl;

    return 0;
}
