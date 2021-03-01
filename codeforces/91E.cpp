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
// const ll MAXN = 

template<typename F = long long>
struct Linear {
    F a, b, id;
    Linear (F ai = 0, F bi = 0, F idd=0) : a(ai), b(bi), id(idd){}
    bool operator < (Linear oth) const {
        return a == oth.a ? b < oth.b : a < oth.a;
    }
    template<typename T> T operator() (T x) const {
      return a*x + b;
    }
};

template<typename F = long long>
struct ConvexHull {
    vector<Linear<F> > f;
    bool cross(Linear<F> P, Linear<F> Q, Linear<F> T ) {
        if (Q.a == T.a) {
            return T.b >= Q.b;
        }
        auto ceil2 = [=](F a, F b) {
            return a >= 0 ? (a + b - 1) / b : a / b;
        };

        F intersect_PQ = ceil2(P.b - Q.b, Q.a - P.a);
        F intersect_QT = ceil2(Q.b - T.b, T.a - Q.a);
        return intersect_QT <= intersect_PQ;
    }

    void getHull() {
        int hull_ptr = 0;
        REP (i, SZ(f)) {
            while (hull_ptr >= 2 && cross(f[hull_ptr-2], f[hull_ptr-1], f[i])) {
                hull_ptr--;
            }
            if (hull_ptr == 1 && f[0].a == f[i].a) {
                hull_ptr--;
            }
            f[hull_ptr++] = f[i];
        }
        f.resize(hull_ptr);
    }

    ConvexHull( vector<Linear<F> > A) : f(A) {
        sort(ALL(f));
        getHull();
    } 
    ConvexHull(){}
    
    pair<F,F> operator() (F x) const {
        int n = f.size();
        auto df = [&](int idx){
            return f[idx+1](x) - f[idx](x);
        };
        if (n == 0) {
            return {-INF, -1};
        }
        int l = 0, r = n - 1;
        while (l < r - 1) {
            int m = (l + r) >> 1;
            if (df(m) < 0) {
                r = m;
            } else {
                l = m;
            }
        }
        return max({pii(f[r](x),f[r].id), pii(f.front()(x),f.front().id), pii(f.back()(x),f.back().id)});
    }

    void mergeHull(const ConvexHull &Q) {
        auto mid = f.size();
        f.insert(f.end(), Q.f.begin(), Q.f.end());
        inplace_merge(f.begin(), f.begin()+mid, f.end());
        getHull();
    }
};

namespace SEGSR {
    const ll MAXN = 200003;
    int n;
    ConvexHull<ll> dt[MAXN*2];

    // params
    const ll les = 0;

    void init(int in) {
        n = in;
        for (int i=n-1;i>0;i--) {
            dt[i] = dt[i<<1];
            dt[i].mergeHull(dt[i<<1|1]);
        }
    }

    ll qry(int l,int r,ll x) {
        pair<ll,ll> ret = {les,-1};
        for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
            if (l&1) {
                ret = max(ret,dt[l++](x));
            }
            if (r&1) {
                ret = max(ret,dt[--r](x));
            }
        }
        debug(ret);
        return ret.Y;
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    int n, q;
    cin >> n >> q;
    REP (i, n) {
        int a, b;
        cin >> a >> b;
        SEGSR::dt[i+n] = ConvexHull<ll>({Linear<ll>(b, a, i+1)});
    }
    SEGSR::init(n);
    
    while (q--) {
        ll l, r, t;
        cin >> l >> r >> t;
        cout << SEGSR::qry(l-1, r, t) << endl;
    }
    return 0;
}
