#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 100005;

int n, q, a;

struct Node {
    vector<int> v, pre;
    void mrg(vector<int> &vl, vector<int> &vr) {
        v = vector<int>(SZ(vl) + SZ(vr));
        auto it = copy(vl.begin(), vl.end(), v.begin());
        copy(vr.begin(), vr.end(), it);
        inplace_merge(v.begin(), it, v.end());

        pre.resize(SZ(v));
        int sum = 0;
        REP (i, SZ(v)) {
            sum += v[i];
            pre[i] = sum;
        }
    }

    int count(int k) {
        return upper_bound(ALL(v), k) - v.begin();
    }

    ll sum(int k) {
        if (v.empty()) {
            return 0;
        }
        int pos = upper_bound(ALL(v), k) - v.begin();
        return pos > 0 ? pre[pos-1] : 0;
    }
} dt[MAXN*2];
// params

void init() {
    for (int i=n-1;i>0;i--) {
        dt[i].mrg(dt[i<<1].v,dt[i<<1|1].v);
    }
}

int qry(int l,int r, int k) { // count element leq than k
    int ret = 0;
    for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
        if (l&1) {
            ret += dt[l++].count(k);
        }
        if (r&1) {
            ret = dt[--r].count(k);
        }
    }
    return ret;
}

ll sum(int l,int r, int k) { // count element leq than k
    ll ret = 0;
    for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
        if (l&1) {
            ret += dt[l++].sum(k);
        }
        if (r&1) {
            ret = dt[--r].sum(k);
        }
    }
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    int n2;
    cin >> n2 >> q;

    n = 1;
    while (n < n2) {
        n <<= 1;
    }
    
    REP (i, n2) {
        cin >> a;
        if (a < 0) {
            a = 0;
        }
        dt[i+n].v.emplace_back(a);
    }
    init();

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        k = min(k, (r - l + 1));
        int L = 0, R = MAXN;
        while (L < R - 1) {
            int mid = (L + R) >> 1;
            if (qry(l-1, r, mid) <= k) {
                L = mid;
            } else {
                R = mid;
            }
        }

        ll ans = sum(l-1, r, L) + R * (k - qry(l - 1, r, L));
        cout << ans << endl;
    }
    return 0;
}
