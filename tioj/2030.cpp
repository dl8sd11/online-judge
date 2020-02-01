#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
// #define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
#define debug(...)
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, q, a[MAXN], mat[MAXN], mav[MAXN], qcnt;
ll ans[MAXN],ans2[MAXN];
struct Query {
    int l, r, val, qid;
};
vector<Query> query;

struct BIT {
    ll bit[MAXN];
    BIT() {
        memset(bit, 0, sizeof(bit));
    }

    void add (int x, int val) {
        for (;x<MAXN;x+=-x&x) {
            bit[x] += val;
        }
    }

    ll qry (int x) {
        ll ret = 0;
        for (;x>0;x-=-x&x) {
            ret += bit[x];
        }
        return ret;
    }
} asum, cdsum;

set<int> app[MAXN];
int lst (int val, int p) {
    auto ptr = app[val].lower_bound(p);
    if (ptr == app[val].begin()) {
        return 0;
    } else {
        return *prev(ptr);
    }
}

int nxt (int val, int p) {
    auto ptr = app[val].lower_bound(p);
    if (ptr == app[val].end()) {
        return n+1;
    } else {
        return *ptr;
    }
}

bool cmp (const Query &q1, const Query &q2) {
    if (q1.l != q2.l) {
        return q1.l > q2.l;
    } else {
        return q1.qid < q2.qid;
    }
}

void CDQ (int l, int r) {
    if (l < r - 1) {
        int mid = (l + r) >> 1;
        CDQ(l, mid);
        CDQ(mid, r);

        int lp=l, rp=mid;

        debug(l, r);
        while (rp < r) {
            if (lp == mid || cmp(query[rp], query[lp])) {
                if (query[rp].qid != -1) {
                    debug(l, r, query[rp].qid, rp, cdsum.qry(query[rp].r));
                    ans[query[rp].qid] += cdsum.qry(query[rp].r);
                }
                rp++;
            } else {
                debug(query[lp].r, query[lp].val);
                cdsum.add(query[lp].r, query[lp].val);
                lp++;
            }
        }

        for (int i=l; i<lp; i++) {
            cdsum.add(query[i].r, -query[i].val);
        }

        sort(query.begin()+l, query.begin()+r, cmp);
    }
}


/*********************GoodLuck***********************/
int main () {
    IOS();
    srand(time(0));
    #ifdef tmd
    n = 1000, q = 5000;
    #else
    cin >> n >> q;
    #endif

    REP1 (i, n) {
        #ifdef tmd
        a[i] = rand()%n + 1;
        cout << a[i] << " \n"[i==n];
        #else
        cin >> a[i];
        #endif
        app[a[i]].insert(i);
        asum.add(i, a[i]);
        query.push_back({lst(a[i], i), i, -a[i], -1});
    }

    REP1 (t, q) {
        int cmd, l, r, p, v;
        #ifdef tmd
        cmd = rand() % 2 ? 1 : 4;
        cout << cmd << " ";
        #else
        cin >> cmd;
        #endif
        if (cmd == 1) {
            #ifdef tmd
            p = rand()%n+1;
            v = rand()%n+1;
            cout << p << " " << v << endl;
            #else
            cin >> p >> v;
            #endif
            if (a[p] == v) {
                continue;
            }

            int nt = nxt(v, p);
            int lt = lst(v, p);
            debug(nt, lt);
            if (nt != n+1) {
                query.push_back({lt, nt, v, -1});
                query.push_back({p, nt, -v, -1});
            }

            query.push_back({lst(a[p], p), p, a[p], -1});
            app[a[p]].erase(p);

            nt = nxt(a[p], p);
            lt = lst(a[p], p);
            if (nt != n+1) {
                query.push_back({p, nt, a[p], -1});
                query.push_back({lt, nt, -a[p], -1});
            }
            app[v].insert(p);
            query.push_back({lst(v, p), p, -v, -1});
            asum.add(p, v-a[p]);
            a[p] = v;
        } else if (cmd == 2) {
            cin >> l >> r >> v;
            mat[l] = r;
            mav[l] = v;
            query.push_back({l, r, v, -1});
        } else if (cmd == 3) {
            cin >> l;
            query.push_back({l, mat[l], -mav[l], -1});
            mat[l] = 0;
        } else {
            #ifdef tmd
            l = rand() %n + 1, r = rand() %n + 1;
            if (l > r) {
                swap(l, r);
            }
            cout << l << " " << r << endl;
            #else
            cin >> l >> r;
            #endif
            #ifdef tmd
            set<int> st;
            for (int e=l; e<=r; e++) {
                st.insert(a[e]);
            }
            ll res = 0;
            for (auto el : st) {
                res += el;
            }
            ans2[qcnt] = res;
            #endif
            ans[qcnt] = asum.qry(r) - asum.qry(l-1);
            query.push_back({l, r, 0, qcnt++});

        }
    }

    for (auto Q : query) {
        debug(Q.l, Q.r, Q.val);
    }

    CDQ(0, SZ(query));

    REP (i, qcnt) {
        debug(ans[i], ans2[i]);
        assert(ans[i] == ans2[i]);
        cout << ans[i] << endl;
    }
}
