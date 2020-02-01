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
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 500005;

int n, q;
int l[MAXN], r[MAXN], c[MAXN], a[MAXN];

pii on[MAXN], off[MAXN];
int onsz, offsz;

int alive[MAXN];
int alisz;

struct Query {
    int first, second, c;
};
Query L[MAXN], R[MAXN];

int main () {
    IOS();
    cin >> n >> q;
    REP (i, q) {
        cin >> l[i] >> r[i] >> c[i];
        L[i] = Query{l[i], r[i], c[i]};
        R[i] = Query{l[i], r[i], c[i]};
    }

    sort(L, L+q, [&](Query p1, Query p2) {
        return p1.first < p2.first;
    });

    sort(R,R+q, [&](Query p1, Query p2) {
        return p1.second < p2.second;
    });
    REP (d, 30) {
        onsz = 0, offsz = 0, alisz = 0;
        REP (j, q) {
            if ((L[j].c & (1<<d)) == 0) {
                off[offsz].first = L[j].first;
                off[offsz].second = L[j].second;
                ++offsz;
            }
            if (R[j].c & (1<<d)) {
                on[onsz].first = R[j].first;
                on[onsz].second = R[j].second;
                ++onsz;
            }
        }

        int idx = 0, mx = -1;
        REP1 (i, n) {
            while (idx<offsz && off[idx].first == i) {
                mx = max(off[idx].second, mx);
                idx++;
            }
            if (mx < i) {
                alive[alisz++] = i;
            }
        }

        REP (i, onsz) {
            on[i].second = *prev(upper_bound(alive, alive+alisz, on[i].second));
        }

        mx = -1;
        idx = 0;



        REP1 (i, n) {
            while (idx<onsz&&on[idx].second==i) {
                if (mx < on[idx].first) {
                    mx = i;
                    a[i] |= (1<<d);
                }
                idx++;
            }
        }
    }

    REP1 (i, n) {
        cout << a[i] << " \n"[i==n];
    }

    #ifdef tmd
    debug(0+1091+20652+8208+100608+66114+7552+32);

    REP (i, q) {
        int sum = 0;
        for (int j=l[i]; j<=r[i]; j++) {
            sum |= a[j];
        }
        debug(sum, c[i]);
        assert(sum == c[i]);
    }

    int ret = 0;
    REP1 (i, n) {
        ret += a[i];
    }
    debug(ret);

    #endif // tmd
}
