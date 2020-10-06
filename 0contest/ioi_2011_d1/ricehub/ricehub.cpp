#include <bits/extc++.h>
#include <ext/pb_ds/tag_and_trait.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> pii;
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define X first
#define Y second
#define eb emplace_back
#define pb push_back
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream& printRng (ostream& os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        if (it == bg) os << *it;
        else os << "," << *it;
    }
    return os << "}";
}
template<typename T> ostream& operator << (ostream& os, const vector<T>& v) {return printRng(os,ALL(v));}
#else
#define debug(...)
#endif
#include "ricehub.h"

ll n;
ll b;
vector<ll> pos;


struct Bit {
    ll N;
    vector<ll> bit;
    Bit (ll sz) : N(sz+3), bit(sz+3) {}
    void add (ll x, ll val) {
        for (x++; x<N; x+=-x&x) {
            bit[x] += val;
        }
    }
    ll qry (ll x) {
        ll res = 0;
        for (x++; x; x-=-x&x) {
            res += bit[x];
        }
        return res;
    }
};

bool check (ll len) {
    Bit sum(n);
    for (ll i=0; i<n; i++) {
        sum.add(i, pos[i]);
        if (i >= len - 1) {
            ll pmid = i - len/2;
            ll L = 1LL*pos[pmid]*(len-len/2) - sum.qry(pmid);
            ll R = sum.qry(n) - sum.qry(pmid) - 1LL*pos[pmid]*(len/2);
            if (L + R <= b) {
                return true;
            }

            sum.add(i-len+1, -pos[i-len+1]);
        }
    }
    return false;
}

int besthub(int R, int L, int X[], long long B) {
    n = R;
    b = B;
    for (ll i=0; i<R; i++) {
        pos.eb(X[i]);
    } 

    ll l = 1, r = R + 1;
    while (l < r - 1) {
        ll m = (l + r) >> 1;
        if (check(m)) {
            l = m;
        } else {
            r = m;
        }
    }

    return l;
}
