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

typedef pair<int,int> pii;
int n, u[MAXN*2], d[MAXN*2];
pii pos[MAXN];

int bu[MAXN*2], bd[MAXN*2];
void add (int x, int val, int* bit) {
    for (; x<MAXN*2; x+=-x&x) {
        bit[x] += val;
    }
}

int qry (int x, int* bit) {
    int ret = 0;
    for (; x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int rqy (int x, int* bit) {
    return qry(MAXN*2-1, bit) - qry(x, bit);
}

ll cnt (int st) {
    ll ret = 0;
    memset(bd, 0, sizeof(bd));
    REP1 (i, n) {
        int c = i + st -1;
        if (c > n) {
            c -= n;
        }
        int id = d[c];

        ret += rqy(pos[id].first, bd);
        add(pos[id].first, 1, bd);
    }
    return ret;
}

/*********************GoodLuck***********************/
int main () {
    IOS();

#ifndef tmd
    freopen("mincross.in", "r", stdin);
    freopen("mincross.out", "w", stdout);
#endif
    cin >> n;

#ifdef tmdd
    vector<int> p, q;
    REP (i, n) {
        p.emplace_back(i+1);
        q.emplace_back(i+1);
    }
    random_shuffle(p.begin(), p.end());
    random_shuffle(q.begin(), q.end());
#endif
    REP1 (i, n) {
#ifdef tmdd
        u[i] = p[i-1];
#else
        cin >> u[i];
#endif
        pos[u[i]].first = i;
    }
    REP1 (i, n) {
#ifdef tmdd
        d[i] = q[i-1];
#else
        cin >> d[i];
#endif
        pos[d[i]].second = i;
    }

    ll base = cnt(1);

    debug(base);

    ll ans = base;
    ll base2 = cnt(1);
    REP1 (i, n) {
        int did = d[i];
        int pu = pos[did].first;

        base -= pu - 1;
        base += n - pu;

        int uid = u[i];
        int pd = pos[uid].second;

        base2 -= pd - 1;
        base2 += n - pd;
#ifdef tmdd
        assert(base == cnt(i+1));
#endif
        ans = min({ans, base, base2});
    }

    cout << ans << endl;
}
