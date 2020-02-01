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
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
vector<int> a;
ll ans = INF;

ll calc (const vector<pair<ll,ll> > &vec) {
    ll sum = 0;
    for (auto v : vec) {
        sum += v.second;
    }

    ll cnt = 0;
    int mid = -1;
    for (auto v : vec) {
        if (cnt + v.second > sum/2) {
            mid = v.first;
            break;
        }
        cnt += v.second;
    }
    debug(mid);

    ll ret = 0;
    for (auto v : vec) {
        ret += abs(mid - v.first) * v.second;
    }

    return ret;
}

void test(ll len) {
    if (len == 1) {
        return;
    }
    ll ret = 0;
    vector<pair<ll,ll> > vp;

    ll cnt = 0;
    REP (i, n) {
        ll cur = a[i] % len;
        if (cnt + cur >= len) {
            vp.emplace_back(i, len - cnt);
            cur -= len - cnt;
            cnt = len;
        }

        if (cnt == len) {
#ifdef tmd
            for (auto v : vp) {
                cout << "{" << v.first << "," << v.second<<"},";
            }
            cout << endl;
#endif
            ret += calc(vp);
            vp.clear();
            cnt = 0;
        }

        if (cur > 0) {
            vp.emplace_back(i, cur);
            cnt += cur;
        }
    }

    debug(len ,ret);
    ans = min(ans, ret);
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n;

    ll sum = 0;
    REP (i, n) {
        int d;
        cin >> d;
        sum += d;
        a.emplace_back(d);
    }

    ll tsum = sum;
    for (ll i=2; i*i<=tsum; i++) {
        if (tsum % i == 0) {
            test(i);
            while (tsum % i == 0) {
                tsum /= i;
            }
        }
    }
    test(tsum);

    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
}
