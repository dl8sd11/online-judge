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

const int MAXN = 1000006;
const int MXSZ = 100000;
const ll MOD = 1000000007;

ll x, k;
vector<vector<ll> > ddiv;
unordered_map<ll,int> id;
vector<ll> dv;

vector<ll> dgen (ll v) {
    vector<ll> rh, rb;
    for (ll i=1; i*i<=v; i++) {
        if (v % i == 0) {
            rh.emplace_back(i);
            rb.emplace_back(v/i);
        }
    }
    if (rh.back() == rb.back()) {
        rb.pop_back();
    }
    rh.insert(rh.end(), rb.rbegin(), rb.rend());
    return rh;
}

void build () {
    id.max_load_factor(0.25);
    dv = dgen(x);
    ddiv.resize(dv.size());
    id.reserve(dv.size());
    REP (i, SZ(dv)) {
        ddiv[i] = dgen(dv[i]);
        id[dv[i]] = i;
    }
}

void mpow (ll ep, vector<ll> &ret) {
    if (ep == 0) {
        ret = {x};
    } else if (ep & 1) {
        vector<ll> dc;
        mpow(ep - 1, dc);
        for (auto v : dc) {
            int pos = id[v];
            for (auto dd : ddiv[pos]) {
                ret.emplace_back(dd);
                if (ret.size() >= MXSZ) {
                    return;
                }
            }
        }
    } else {
        vector<ll> dc;
        mpow(ep>>1, dc);
        vector<int> ed = {-1};
        REP (i, SZ(dc)) {
            if (ed.size() == 1 || dc[i] > dc[ed.back()]) {
                ed.emplace_back(i);
            }
        }
        for (auto v : dc) {
            int pos = id[v];
            for (int ppos=ed[pos]+1; ppos<=ed[pos+1]; ppos++) {
                debug(v, ppos);
                int pos2 = id[dc[ppos]];
                for (auto dd : ddiv[pos2]) {
                    ret.emplace_back(dd);
                    if (ret.size() >= MXSZ) {
                        return;
                    }
                }
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> x >> k;
    build();
    vector<ll> ans;
    mpow(min(ll(MXSZ), k), ans);

    for (auto v : ans) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
