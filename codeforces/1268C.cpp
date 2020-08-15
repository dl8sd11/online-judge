#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
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
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 200005;
const ll MOD = 1000000007;

int n, a[MAXN], p[MAXN], l, r;

struct Seg {
    ll dt[MAXN*4], tag[MAXN*4], sz[MAXN*4];

    void build (int o, int nL, int nR) {
        if (nL == nR - 1) {
            sz[o] = 1;
            return;
        } else {
            sz[o] = nR - nL;
            int nM = (nR + nL) >> 1;
            build(o<<1, nL, nM);
            build(o<<1|1, nM, nR);
        }
    }

    ll get (int o) {
        return dt[o] + sz[o] * tag[o];
    }

    void push (int o) {
        if (tag[o]) {
            tag[o<<1] += tag[o];
            tag[o<<1|1] += tag[o];
            dt[o] += tag[o] * sz[o];
            tag[o] = 0;
        }
    }

    void pull (int o) {
        dt[o] = get(o<<1) + get(o<<1|1);
        sz[o] = sz[o<<1] + sz[o<<1|1];
    }

    void add (int qL, int qR, int val, int o, int nL, int nR) {
        if (qL >= nR || qR <= nL || qL >= qR) {
            return;
        } else if (qL <= nL && nR <= qR) {
            tag[o] += val;
        } else {
            push(o);
            int nM = (nL + nR) >> 1;
            add(qL, qR, val, o<<1, nL, nM);
            add(qL, qR, val, o<<1|1, nM, nR);
            pull(o);
        }

    }

    ll qry (int qL, int qR, int o, int nL, int nR) {
        if (qL >= nR || qR <= nL || qL >= qR) {
            return 0;
        } else if (qL <= nL && nR <= qR) {
            return get(o);
        } else {
            push(o);
            int nM = (nL + nR) >> 1;
            return qry(qL, qR, o<<1, nL, nM) + qry(qL, qR, o<<1|1, nM, nR);
        }

    }

    void reset (int x, int o, int nL, int nR) {
        if (x >= nR || x < nL) {
            return;
        } else if (nL == nR - 1) {
            sz[o] = 0;
            dt[o] = 0;
            tag[o] = 0;
        } else {
            int nM = (nL + nR) >> 1;
            push(o);
            reset(x, o<<1, nL, nM);
            reset(x, o<<1|1, nM, nR);
            pull(o);
        }

    }
} LS, RS;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> rk;


int bit[MAXN];
void add (int x, int d) {
    for (;x<MAXN; x+=-x&x) {
        bit[x] += d;
    }
}
 
int sum (int x) {
    int ret = 0;
    for (;x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP1 (i, n) {
        cin >> a[i];
        p[a[i]] = i;
    }


    LS.build(1, 1, n+1);
    RS.build(1, 1, n+1);

    ll ans = 0;
    LS.add(1, p[1], 1, 1, 1, n+1);
    RS.add(p[1]+1, n+1, 1, 1, 1, n+1);
    LS.reset(p[1], 1, 1, n+1);
    RS.reset(p[1], 1, 1, n+1);

    rk.insert(p[1]);
    add(p[1], 1);

    vector<ll> opt = {0};
    for (int i=2; i<=n; i++) {
        LS.add(1, p[i], 1, 1, 1, n+1);
        RS.add(p[i]+1, n+1, 1, 1, 1, n+1);
        LS.reset(p[i], 1, 1, n+1);
        RS.reset(p[i], 1, 1, n+1);

        rk.insert(p[i]);
        int mid = *rk.find_by_order(i/2);

        ans += sum(n) - sum(p[i]);
        add(p[i], 1);
        ll mrg = LS.qry(mid+1, n+1, 1, 1, n+1) + RS.qry(1, mid, 1, 1, n+1);
        debug(ans, mrg, mid);

        opt.eb(ans + mrg);
    }
    

    for (auto v : opt) {
        cout << v << " ";
    }
    cout << endl;
}

