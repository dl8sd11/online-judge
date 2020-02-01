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
const ll MAXN = 51;

#define SQ(x) ((x)*(x))

int n;
pair<double,double> pts[MAXN];


pdd operator - (pdd p1 ,pdd p2) {
    return {p1.X-p2.X,p1.Y-p2.Y};
}

pdd operator + (pdd p1 ,pdd p2) {
    return {p1.X+p2.X,p1.Y+p2.Y};
}

pdd dv (pdd p1, double p2) {
    return {p1.X/p2,p1.Y/p2};
}

pdd ml (pdd p1, double p2) {
    return {p1.X*p2,p1.Y*p2};
}

pdd pen (pdd p1) {
    return {p1.Y, -p1.X};
}

double operator * (pdd p1 ,pdd p2) {
    return {p1.X*p2.Y-p1.Y*p2.X};
}

pair<double,double> getCen (int i, int j, int k) {
    pdd p1 = dv((pts[i]+pts[j]),2.0);
    pdd p2 = dv((pts[i]+pts[k]),2.0);
    pdd p3 = p1 + pen(pts[i]-pts[j]);
    pdd p4 = p2 + pen(pts[i]-pts[k]);

    double a134 = (p4-p1)*(p3-p1);
    double a123 = (p3-p1)*(p2-p1);

    pdd vec = ml((p4-p2), a123/(a123+a134));
    return p2 + vec;
}

const double eps = 1e-7;
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> pts[i].X >> pts[i].Y;
    }
    debug(getCen(1,0,2));

    double ans = 1e10;
    REP (i, n) {
        REP (j, i+1) {
            REP (k, j) {
                pair<double,double> cen;
                if (i == j) {
                    cen = dv((pts[i]+pts[k]),(2.0));
                } else {
                    cen = getCen(i, j, k);
                }
                debug(i, j, k,cen);

                double r2 = SQ(pts[i].X-cen.X) + SQ(pts[i].Y-cen.Y);
                bool flag = true;
                REP (l, n) {
                    double dis = SQ(pts[l].X-cen.X) + SQ(pts[l].Y-cen.Y);
                    if (sqrt(dis) > sqrt(r2) + eps) {
                        flag = false;
                        break;
                    }
                }

                if (flag) {
                    ans = min(ans, sqrt(r2));
                }

            }
        }
    }

    cout << fixed << setprecision(10) << ans << endl;

    return 0;
}
