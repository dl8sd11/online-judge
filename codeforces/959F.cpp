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

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, q, a[MAXN];
ll ans[MAXN];


struct Query {
    int l, x, id;
    bool operator < (const Query &oth) const {
        return l < oth.l;
    }
};
vector<Query> qry;

ll mpow (ll bs, ll ep) {
    ll ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = ret * bs % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return ret;
}

const int MAXD = 21;
int ba[MAXD], sz;

void insertB (int vec) {
    for (int i=MAXD; i>=0; i--) {
        if (vec>>i & 1) {
            if (ba[i] == 0) {
                ba[i] = vec;
                sz++;
                return;
            } else {
                vec ^= ba[i];
            }
        }
    }
}

bool check (int vec) {
    for (int i=MAXD; i>=0; i--) {
        if (vec>>i & 1) {
            if (ba[i]) {
                vec ^= ba[i];
            }
        }
    }
    return vec == 0;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q;
    REP1 (i, n) {
        cin >> a[i];
    }

    for (int i=0; i<q; i++) {
        int l, x;
        cin >> l >> x;
        qry.push_back({l, x, i});
    }

    sort(ALL(qry));
    debug("sorted");

    int idx = 0;
    for (int i=1; i<=n; i++) {
        insertB(a[i]);

        while (idx < q && qry[idx].l == i) {
            if (check(qry[idx].x)) {
                int fr = i - sz;
                ans[qry[idx].id] = mpow(2, fr);
            } else {
                ans[qry[idx].id] = 0;
            }
            idx++;
        }
    }

    for (int i=0; i<q; i++) {
        cout << ans[i] << endl;
    }

}
