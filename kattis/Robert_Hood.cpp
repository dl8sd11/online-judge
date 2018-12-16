#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;


ll n;
pii p[MAXN];
vector<pii> hull;
pii sub(pii a,pii b) {
    return {a.X-b.X,a.Y-b.Y};  
}
ll cross(pii a,pii b) {
    return a.X*b.Y - a.Y*b.X;
}
void convex_hull() {
    sort(p,p+n);
    ll cnt = 0;
    REP (i,n) {
        while (SZ(hull) > 1 && cross(sub(hull[cnt-1],hull[cnt-2]),sub(p[i],hull[cnt-1])) >= 0) {
            hull.pop_back();
            cnt--;
        }
        hull.push_back(p[i]);
        cnt++;
    }

    ll lh = cnt;
    for (ll i=n-2;i>=0;i--) {
        while (SZ(hull) > lh && cross(sub(hull[cnt-1],hull[cnt-2]),sub(p[i],hull[cnt-1])) >= 0) {
            hull.pop_back();
            cnt--;
        }
        hull.push_back(p[i]);
        cnt++;
    }

}

double dis(pii a,pii b) {
    return sqrt((a.X-b.X)*(a.X-b.X)+(a.Y-b.Y)*(a.Y-b.Y));
}
double longest_distance() {
    ll anti = 1;
    double ans = 0.0;
    ll m = SZ(hull)-1;

    REP (i,m) {
        pii cur = sub(hull[i+1],hull[i]);
        while (cross(cur,sub(hull[anti],hull[i])) > cross(cur,sub(hull[anti+1],hull[i]))) {
            anti++;
            if (anti >= m) {
                anti -= m;
            }
        }
        debug(i,anti);
        ans = max(ans,max(dis(hull[anti],hull[i]),dis(hull[anti],hull[i+1])));
    }
    return ans;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> p[i].X >> p[i].Y;
    }

    convex_hull();
    debug(hull);
    cout << fixed << setprecision(10) << longest_distance() << endl;

    return 0;
}
