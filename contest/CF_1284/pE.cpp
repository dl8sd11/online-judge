#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
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
#define TIME(i) Timer i(#i)
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
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 2503;

int n;
pair<int,int> p[MAXN];
ll sum;

pii operator - (const pii &p1, const pii &p2) {
    return {p1.X-p2.X, p1.Y-p2.Y};
}
ll operator * (const pii &p1, const pii &p2) {
    return {1LL*p1.X*p2.Y-1LL*p1.Y*p2.X};
}

const double PI = acos(-1);
double deg(pii p) {
    double len = sqrt(1.0*p.X*p.X+1.0*p.Y*p.Y);
    return acos(p.X/len) + PI * (p.Y < 0);
}

ll C(ll a, ll b) {
    ll ret = 1;
    REP (i, b) {
        ret *= (a-i);
    }
    REP (i, b) {
        ret /= i+1;
    }
    return ret;
}

bool hf (pii pt) {
    if (pt.Y == 0) {
        return pt.X < 0;
    } else {
        return pt.Y < 0;
    }
}

void calc (int cen) {
    vector<pair<int,int> > vec;
    REP (i, n) {
        if (i != cen) {
            vec.emplace_back(p[i]-p[cen]);
        }
    }
    sort(ALL(vec), [&](pii p1, pii p2) {
        bool dw1 = hf(p1);
        bool dw2 = hf(p2);
        if (dw1 != dw2) {
            return dw2;
        } else {
            return p1*p2 > 0;
        }
    });
    debug(cen, vec);

    vector<pii> nw;
    REP (u, 2) {
        for (auto v : vec) {
            nw.emplace_back(v);
        }
    }

    int idx = 0;
    for (int i=0;i<n-1;i++) {
        idx = max(idx, i);
        while ((idx+1)-i+1<=n-1 && nw[i]*nw[idx+1]>0) {
            idx++;
        }

        ll sz = idx - i;
        if (sz >= 3) {
            sum += C(sz,3);
        }
    }
}


/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> p[i].X >> p[i].Y;
    }
    REP (i, n) {
        calc(i);
    }
    debug(sum);

    cout << C(n,5)*5 - sum << endl;

    return 0;
}
