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

ll t, n;
ll s, l[MAXN], r[MAXN], lv[MAXN], rv[MAXN], qcnt;
vector<ll> val;

struct Query {
    ll t, id, add;
    bool operator < (const Query &q) {
        return t > q.t;
    }
} query[MAXN];

ll bex[MAXN*2], bsu[MAXN*2];
void add (ll x, ll vv, ll *bit) {
    for (;x<MAXN*2; x+=-x&x) {
        bit[x] += vv;
    }
}

ll qry (ll x, ll *bit) {
    ll ret = 0;
    for (;x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

ll lbd (ll x) {
    ll L = -1, R = MAXN*2;
    while (L <  R- 1) {
        ll mid = (L+R) >> 1;
        if (qry(mid, bex) >= x) {
            R=  mid;
        } else {
            L = mid;
        }
    }
    return R;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n >> s;
        val.clear();
        ll base = 0;
        REP (i, n) {
            cin >> l[i] >> r[i];
            base += l[i];
            val.emplace_back(l[i]);
            val.emplace_back(r[i]);
        }
        sort(val.begin(), val.end());
        val.resize(unique(val.begin(), val.end())-val.begin());
        qcnt = 0;
        REP (i, n) {
            lv[i] = lower_bound(val.begin(), val.end(), l[i])-val.begin()+1;
            rv[i] = lower_bound(val.begin(), val.end(), r[i])-val.begin()+1;
            query[qcnt++] = {r[i], i, 1};
            query[qcnt++] = {l[i]-1, i, -1};
        }

        sort(query, query+qcnt);

        ll Rsum = 0;
        ll Rcnt = 0;
        ll Lcnt = n;
        ll ans = 0;
        for (ll i=0; i<qcnt; ) {
            ll bs = i;
            while (i<qcnt&&query[i].t == query[bs].t) {
                debug(i);
                Query cur = query[i];
                add(lv[cur.id], cur.add, bex);
                add(lv[cur.id], l[cur.id]*cur.add, bsu);

                if (cur.add < 0) {
                    Rsum += l[cur.id];
                    Rcnt++;
                } else {
                    Lcnt--;
                }
                i++;
            }

            if (i == qcnt) {
                break;
            }

            debug(bs);
            ll X = query[bs].t;
            debug(bs);

            ll inBit = qry(MAXN*2-1, bex);
            debug(X);
            ll b = lbd(n/2-Lcnt);
            ll a = lbd(qry(b-1,bex));
            if (inBit+Rcnt >= n/2+1 && b<MAXN*2 && inBit) {
                debug("HI");

                ll ls = qry(a, bsu);
                ll frc = n/2-Lcnt-qry(a, bex);
                ls += b*frc;
                ll dl = qry(MAXN*2-1, bsu) - ls;

                ll rem = base - dl;
                debug(rem, dl, ls, frc, a, b, inBit);
                ll srem = s - rem;

                ll gt = min(X, srem / (inBit - qry(a, bex)));

                if (gt > query[i].t) {
                    ans = max(ans, gt);
                }
                debug(inBit, qry(a,bex), X, a, b, gt, srem);


            }
        }

        cout << ans << endl;

    }

}
