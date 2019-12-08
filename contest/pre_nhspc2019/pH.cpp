#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("03","unroll-loops")
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define MEM(a,b) memset(a,(b),sizeof(a))
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d: (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
template<typename T> ostream &operator << (ostream &os, const pair<T,T> &p){return os<<"("<<p.first<<","<<p.second<<")";}
template<typename IT> ostream &_printRng(ostream &os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        os << (it==bg?"":",") << *it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os, const vector<T> &vec) {return _printRng(os, vec.begin(),vec.end());}
template<typename IT> void pary (IT bg, IT ed) {_printRng(cerr,bg,ed);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 100005;
int n, q, c, a[MAXN];
struct Bit {
    int dt[MAXN];
    void add (int x, int val) {
        for (x++; x<MAXN; x+=-x&x) {
            dt[x] += val;
        }
    }

    int qry (int x) {
        int ret = 0;
        for (x++; x>0; x-=-x&x) {
            ret += dt[x];
        }
        return ret;
    }

    int qry (int l, int r) {
        return qry(r) - qry(l-1);
    }
} bit[11];

ll qry (int l1, int r1, int l2, int r2) {
    ll ret = 0;
    REP (d, 11) {
        ret += 1LL * bit[d].qry(l1, r1) * bit[d].qry(l2, r2);
    }
    return ret;
}

int pry (int l1, int r1, int l2, int r2) {
    map<int,int> cl, cr;
    for (int i=l1; i<=r1; i++) {
        cl[a[i]]++;
    }
    for (int i=l2; i<=r2; i++) {
        cr[a[i]]++;
    }

    int ret = 0;
    for (auto p : cl) {
        ret += p.second * cr[p.first];
    }

    return ret;
}

int main () {
    IOS();

    cin >> n >> q >> c;
    debug(n, q);
    REP (i, n) {
        cin >> a[i];

        if (n > 5000 || q > 5000) {
            bit[a[i]].add(i, 1);
        }
    }
    REP (i, q) {
        int cmd, x, y;
        cin >> cmd;
        if (cmd == 1) {
            cin >> x >> y;
            if (n > 5000 || q > 5000) {
                bit[a[x]].add(x, -1);
            }
            a[x] = y;

            if (n > 5000 || q > 5000) {
                bit[a[x]].add(x, 1);
            }

        } else {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;

            if (n > 5000 || q > 5000) {
                cout << qry(l1, r1, l2, r2) << endl;
            } else {
                debug("test");
                cout << pry(l1, r1, l2, r2) << endl;
            }
        }
    }


}
