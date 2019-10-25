#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
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

int n, m;
ll l[MAXN], r[MAXN], ans[MAXN];
bool no_sol;

struct Edge {
    ll first, second, id;
    bool operator < (const Edge &edg) const {
        return first < edg.first;
    }
};
vector<Edge> rng;
vector<pii> len;
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> m;
    REP (i, n) {
        cin >> l[i] >> r[i];
        if (i > 0) {
            rng.push_back({l[i]-r[i-1], r[i]-l[i-1], i});
        }
    }

    REP (i, m) {
        ll d;
        cin >> d;
        len.emplace_back(d, i+1);
    }

    sort(len.begin(), len.end());
    sort(rng.begin(), rng.end());

    priority_queue<pii,vector<pii>,greater<pii> > pq;
    int idx = 0;
    for (int i=0; i<SZ(len); i++) {
        while (idx < n-1 && rng[idx].first <= len[i].first) {
            pq.emplace(rng[idx].second, rng[idx].id);
            idx++;
        }
        if (pq.empty()) {
            continue;
        }
        if (len[i].first > pq.top().first) {
            break;
        } else {

            ans[pq.top().second] = len[i].second;
            pq.pop();
        }
    }


    if (idx != n-1 || !pq.empty()) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        REP1 (i, n-1) {
            cout << ans[i] << " \n"[i==n-1];
        }
    }
}
