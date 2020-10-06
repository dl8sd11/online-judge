#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define X first
#define Y second
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream &__printRng (ostream& os, IT bg, IT ed) {
    for (IT it=bg; it!=ed; it++) {
        if (it == bg) os << "{" << *it;
        else os << "," << *it;
    }
    return os << "}";
}
template<typename T> ostream &operator << (ostream& os, const vector<T> &vec) {
    return __printRng(os,ALL(vec));
}
#else
#define debug(...)
#endif

#include"holiday.h"

struct KSum {
    int k = 0, ptr = 0;
    multiset<int> mx;
    multiset<int> mn;
    ll sum = 0;

    void inc () {
        assert(mn.size());
        auto ptr = prev(mn.end());
        mx.insert(*ptr);
        sum += *ptr;
        mn.erase(ptr);
        k++;
    }
    
    void dec () {
        assert(mx.size());
        auto ptr = mx.begin();
        mn.insert(*ptr);
        sum -= *ptr;
        mx.erase(ptr);
        k--;
    }

    void add (int val) {
        mn.insert(val);
        if (mx.size()) {
            dec();
            inc();
        }
    }
};
ll solve (int n, int s, int d, vector<int> a) {
    if (d == 0) return 0;
    vector<pii> sg;

    for (int i=s+1; i<n; i++) {
        if (a[i]) {
            sg.eb(a[i], i);
        }
    }
    sg.eb(0, n);
    sg.eb(0, n+1);

    vector<ll> msg(d+1, 0);
    KSum l, r;
    l.add(sg[0].X);
    r.add(sg[0].X);
    r.add(sg[1].X);
    int ptr = 0;
    for (int i=2, lptr, rptr; i<=d; i++) {

        lptr = sg[ptr].Y - s;
        rptr = sg[ptr+1].Y - s;
        while (l.k < ptr+1 && l.k+lptr < i) {
            l.inc();
        }
        while (r.k < ptr+2 && r.k+rptr < i) {
            r.inc();
        }
        while (ptr < SZ(sg)-2 && r.sum > 0 && r.sum >= l.sum) {
            debug(ptr, SZ(sg));
            ptr++;
            lptr = sg[ptr].Y - s;
            rptr = sg[ptr+1].Y - s;
            l.add(sg[ptr].X);
            r.add(sg[ptr+1].X);
            debug(ptr, SZ(sg));
            if (l.k) {
                l.dec();
            }
            if (r.k) {
                r.dec();
            }
            while (l.k < ptr+1 && l.k+lptr < i) {
                l.inc();
            }
            while (r.k < ptr+2 && r.k+rptr < i) {
                r.inc();
            }
            debug(lptr, rptr, l.sum, r.sum, l.k, r.k);
        }
        debug(lptr, rptr, i, l.sum, r.sum);
        debug(l.k, r.k);
        msg[i] = l.sum;
    }
    debug(msg);
    return max(a[s] + msg[d-1], msg[d]);
}

long long int full (int n, int start, int d, int attraction[]) {
    vector<int> a;
    for (int i=0; i<n; i++) {
        a.eb(attraction[i]);
    }

    ll la = solve(n, start, d, a);
    reverse(ALL(a));
    ll ra = solve(n, n-1-start, d, a);

    return max(la, ra);
}


ll start_left (int n, int start, int d, int *a) {
    assert(start == 0);
    ll ans = 0;
    for (ll mn=1002; mn>=0; mn--) {

        ll cnt = 0;
        ll cur = 0;
        for (ll i=0; i<n; i++) {
            if (a[i] >= mn) {
                cnt++;
                cur += a[i];
            }
            if (cnt + i > d) break;
            ans = max(ans, cur);
        }
    }
    if (d == 0) assert(ans == 0);

    //assert(ans == full(n, start, d, a));
    return ans;

}

ll bf (int n, int start, int d, int *a) {
    ll ans = 0;
    for (int i=start; i>=0; i--) {
        for (int j=start; j<n; j++) {
            vector<int> v;
            for (int k=i; k<=j; k++) v.eb(a[k]);
            sort(ALL(v));

            ll cur = 0;
            int ld = abs(i-start), rd = abs(j-start);
            int dd = min(ld, rd) + ld + rd;
            for (int k=0; k<min(SZ(v),d-dd); k++) {
                cur += v[SZ(v)-k-1];
            }
            ans = max(ans, cur);

        }
    }

    return ans;
}

long long int findMaxAttraction (int n, int start, int d, int attraction[]) {
    vector<int> v;
    for (int i=0; i<n; i++) v.eb(attraction[i]);
    debug(n, start, d);
    debug(v);

    ll lf = full(n, start,d, attraction);

#ifdef tmd
    ll ba = bf(n, start, d, attraction);
    debug(lf, ba);
    assert(lf == ba);
#endif
    return lf;
}
