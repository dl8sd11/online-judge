#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
using namespace std;
typedef unsigned int ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,const vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;


int n, m;
ll ans[MAXN];
vector<ll> val;

struct Query {
    int l, r, id;
    bool operator < (const Query &oth) const {
        return l > oth.l;
    }

    void rev () {
        l = n - l - 1;
        r = n - r - 1;
        swap(l, r);
    }
};
vector<Query> query;

struct SegmentTree {
    int dt[MAXN*2];

    SegmentTree () {
        fill(dt, dt+n*2, n);
    }

    void upd (int x, int v) {
        for (dt[x+=n]=v; x>1; x>>=1) {
            dt[x>>1] = min(dt[x], dt[x^1]);
        }
    }

    int qryMax (int l, int r) {
        int ret = n;
        for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l&1) {
                ret = min(ret, dt[l++]);
            }
            if (r&1) {
                ret = min(ret, dt[--r]);
            }
        }
        return ret;
    }
};

struct Bit {
    ll dt[MAXN];

    Bit () {
        memset(dt, INF, sizeof(dt));
    }

    void upd (int x, ll v) {
        for (++x; x<MAXN; x+=-x&x) {
            dt[x] = min(dt[x], v);
        }
    }

    ll qryMin (int x) {
        ll ret = INF;
        for (++x; x>0; x-=-x&x) {
            ret = min(ret, dt[x]);
        }
        return ret;
    }
};

void solve (const vector<ll> &a) {
    vector<int> ca(n);
    REP (i, n) {
        ca[i] = lower_bound(val.begin(),val.end(), a[i])-val.begin();
    }
    sort(query.begin(), query.end());

    SegmentTree lst;
    Bit pre;
    int idx = n-1;
    for (const Query &cur : query) {
        while (cur.l <= idx) { // update bit
            int pt = lst.qryMax(ca[idx], n);
            while (pt != n) {
                pre.upd(pt, a[pt]>a[idx] ? (a[pt]-a[idx]) : (a[idx]-a[pt]));
                if (a[pt] == a[idx]) {
                    break;
                }

                ll ubd = a[pt];
                ll mid = (ubd + a[idx]) >> 1;

                int vr = upper_bound(val.begin(), val.end(), mid)-val.begin();
                pt = lst.qryMax(ca[idx], vr);
            }

            lst.upd(ca[idx], idx);
            idx--;
        }

        ans[cur.id] = min(ans[cur.id], pre.qryMin(cur.r));
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    memset(ans, INF, sizeof(ans));

    cin >> n;
    vector<ll> a(n);
    REP (i, n) {
        cin >> a[i];
        val.emplace_back(a[i]);
    }
    // compress the value
    sort(val.begin(), val.end());
    val.resize(unique(val.begin(), val.end())-val.begin());

    cin >> m;
    query.resize(m);
    REP (i, m) {;
        cin >> query[i].l >> query[i].r;
        query[i].l--, query[i].r--;
        query[i].id = i;
    }

    solve(a);
    reverse(a.begin(), a.end());
    for (Query &el : query) {
        el.rev();
    }
    solve(a);

    REP (i, m) {
        cout << ans[i] << endl;
    }
}
