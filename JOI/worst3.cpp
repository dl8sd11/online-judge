#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> ostream &operator << (ostream &os,deque<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 500005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, q;
ll d[MAXN];

struct Data {
    ll l, r, d;
};

ostream& operator << (ostream &os, const Data &dt) {
    return os << "{" << dt.l << "," << dt.r << "," << dt.d << "}";
}

deque<Data> deq;
void build () {
    deq.push_back({0LL,0LL, 1});
    for (int i=1;i<=n;i++) {
        if (d[i] <= deq.back().d) {
            deq.back().r = i;
        } else {
            ll mul = (d[i] + deq.back().d - 1) / deq.back().d;
            deq.push_back({i,i, mul*deq.back().d});
        }
    }
}

ll qry (ll t, ll l, ll r) {
    ll sum = 0;
    for (const auto &D : deq) {
        ll mul = t / D.d;
        ll nL = -D.r + D.d * mul;
        ll nR = -D.l + D.d * mul;
        debug(D);
        debug(nL, nR, l, r);
        nL = max(nL, l);
        nR = min(nR, r);
        sum += max(0LL, (nR - nL) + 1);
    }
    return sum;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q;
    REP1 (i, n) {
        cin >> d[i];
    }
    build();
    debug(deq);

    while (q--) {
        ll t, l, r;
        cin >> t >> l >> r;
        cout << qry(t, l, r) << endl;
    }
}
/*
6 6
11
36
28
80
98
66
36 29 33
190 171 210
18 20 100
1000 900 1100
92 87 99
200 100 300
*/
