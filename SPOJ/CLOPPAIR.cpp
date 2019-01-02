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
#define SQ(i) (i)*(i)
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

struct point{
    ll X,Y,id;
};
point p[MAXN],t[MAXN];
ll n;
struct ans {
    ll dis,i,j;
};

ans solve(ll L,ll R) {
    if (L >= R - 1) {
        return {INF,-1,-1};
    }
    ll mid = L+R>>1;

    ans ret = {INF,-1,-1};

    ans la = solve(L,mid),ra = solve(mid,R);
    if (la.dis < ret.dis) {
        ret = la;
    }
    if (ra.dis < ret.dis) {
        ret = ra;
    }

    ll cnt = 0;
    for (ll i=mid-1;i>=L&&p[mid].X-p[i].X<ret.dis;i--) {
        t[cnt++] = p[i];
    }

    for (ll i=mid;i<R&&p[i].X-p[mid].X<ret.dis;i++) {
        t[cnt++] = p[i];
    }

    sort(t,t+cnt,[](const point &a,const point &b){return a.Y < b.Y;});

    debug(cnt);
    REP (i,cnt) {
        REP1 (j,3) {
            if (i + j >= cnt) {
                break;
            }
            ll sqd = SQ(t[i].X-t[i+j].X)+SQ(t[i].Y-t[i+j].Y);
            if (sqd < ret.dis) {
                ret = {sqd,t[i].id,t[i+j].id};
            }
        }
    }
    
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        p[i].id = i;
        cin >> p[i].X >> p[i].Y;
    }

    sort(p,p+n,[](const point &a,const point &b){return a.X < b.X;});

    ans ret = solve(0,n);
    
    cout << min(ret.i,ret.j) << " " << max(ret.i,ret.j) << " " << fixed << setprecision(6) << sqrt(ret.dis) << endl;

    return 0;
}
