//#pragma GCC optimize("O3","unroll-loops")
//#pragma GCC target("avx","avx2","fma")
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
const int MOD = 1000000007;

int n, d[MAXN], q;

const int sz = 5;

template<typename T>
struct DEQUE {
    T dt[MAXN];
    int hd = 0, ed = 0;

    DEQUE() {
        hd = ed = 0;
    }

    void clear () {
        hd = ed = 0;
    }

    void eb (int x, int y) {
        dt[ed] = {x,y};
        ed++;
    }

    int size () {
        return ed - hd;
    }

    bool empty () {
        return size() == 0;
    }

    T front () {
        return dt[hd];
    }

    T back () {
        return dt[ed-1];
    }

    void pop_back() {
        ed--;
    }

    void pop_front() {
        hd++;
    }
};
DEQUE<pii> deq[sz];
/*********************GoodLuck***********************/

int main () {
    IOS();

    cin >> n;


    REP1 (i, n) {
        cin >> d[i];
    }

    cin >> q;

    int dp = 0;
    REP1 (_u_, q) {
        int k;
        cin >> k;

        REP (i, sz) {
            deq[i].clear();
        }



        deq[0].eb(d[1], 1);
        int mn = 0;
        int mx = 0;

        for (int i=2; i<=n; i++) {
            pii bst = {mn, MOD};

            assert(mn >= mx - 2);
            for (int j=mn; j<=mx; j++) {
                while (deq[j%sz].size() && deq[j%sz].front().Y <= i-k-1) {
                    deq[j%sz].pop_front();
                }
                int cur = MOD;
                if (deq[j%2].size()) {
                    if (deq[j%sz].front().X > d[i]) {
                        cur = j;
                    } else {
                        cur = j + 1;
                    }
                }
                if (cur < bst.Y) {
                    bst = {j, cur};
                }
            }
            debug(bst.X, bst.Y);

            dp = bst.Y;
            while (deq[dp%sz].size() && deq[dp%sz].back().X <= d[i]) {
                deq[dp%sz].pop_back();
            }

            while (deq[mn%sz].empty()) {
                mn++;
            }
            deq[dp%sz].eb(d[i], i);
            mx = max(mx, dp);
        }

        cout << dp << '\n';
    }
}
