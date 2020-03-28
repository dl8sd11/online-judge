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

const int MAXN = 1000005;
const ll MOD = 1000000007;


int sz;
struct Segment {
    pii seg[MAXN*4]; // bst, cnt

    pii mrg (const pii &p1, const pii &p2) const {
        if (p1.X == p2.X) {
            return {p1.X, (p1.Y + p2.Y) % MOD};
        } else {
            return p1.X < p2.X ? p1 : p2;
        }
    }

    pii qry (int l,int r) {
        pii res = {MOD, -1};
        for (l+=sz, r+=sz; l<r; l>>=1, r>>=1) {
            if (l&1) {
                res = mrg(res, seg[l++]);
            }
            if (r&1) {
                res = mrg(res, seg[--r]);
            }
        }
        return res;
    }

    void chg (int x, pii cur) {
        for (seg[x+=sz]=cur; x>1; x>>=1) {
            seg[x>>1] = mrg(seg[x], seg[x^1]);
        }
    }
} dp;

int z;
vector<pii> seg;
int n, m, L[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> z;
    while (z--) {
        cin >> n >> m;
        seg.clear();
        memset(L, 0, sizeof(L));

        vector<int> val;
        REP (i, m) {
            int a, b;
            #ifdef tmd
            a = rand() % n;
            b = rand() % (n-a) + a + 1;
            #else
            cin >> a >> b;
            #endif // tmd

            seg.eb(a, b);
            val.eb(a);
            val.eb(b);
        }

        sort(ALL(val));
        val.resize(unique(ALL(val))-val.begin());

        for (auto &p : seg) {
            p.X = lower_bound(ALL(val), p.X) - val.begin();
            p.Y = lower_bound(ALL(val), p.Y) - val.begin();

            L[p.Y+1] = max(L[p.Y+1], p.X+1);
//            debug(p.X, p.Y, L[p.Y+1]);
        }

        debug(val);

        sz = SZ(val) + 1;
        dp.chg(0, pii(0, 1));

        int lst = 0;

        pii ans;
        for (int i=1; i<=SZ(val); i++) {
            lst = max(lst, L[i]);

            pii cur = dp.qry(lst, i);
            cur.X++;
            ll mul = i == SZ(val) ? 1 : (val[i] - val[i-1]);
            cur.Y = 1LL * cur.Y * mul % MOD;

            if (i == SZ(val)) {
                ans = cur;
                ans.X--;
            } else {
                dp.chg(i, cur);
            }
        }



        cout << ans.X << " " << ans.Y << endl;



    }


}
/*
2
11 4
1 4
6 8
2 7
9 10
3 2
1 2
2 3
*/
