#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
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
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 100005;

int n, p[MAXN];
ll ans;

int dt[MAXN*2];

const int les = 0;
inline int opr(int v1,int v2) {
    return max(v1,v2);
}
inline void up(int &x,int val) {
    x = val;
}

void init() {
    for (int i=n-1;i>0;i--) {
        dt[i] = opr(dt[i<<1],dt[i<<1|1]);
    }
}

int qry(int l,int r) {
    int ret = les;
    for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
        if (l&1) {
            ret = opr(ret,dt[l++]);
        }
        if (r&1) {
            ret = opr(ret,dt[--r]);
        }
    }
    return ret;
}

int find_lft (int idx, int val) {
    int l = -1, r = idx;
    while (l < r - 1) {
        int m = (l + r) >> 1;
        if (qry(m, idx) > val) {
            l = m;
        } else {
            r = m;
        }
    }
    return l;
}

int find_rgt (int idx, int val) {
    int l = idx, r = n;
    while (l < r - 1) {
        int m = (l + r) >> 1;
        if (qry(idx+1, m+1) > val) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}


/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> p[i];
        dt[i+n] = p[i];
    }
    init();

    REP (i, n) {
        int l1 = find_lft(i, p[i]);
        int r1 = find_rgt(i, p[i]);
        debug(l1, r1);
        if (l1 != -1) {
            int l2 = find_lft(l1, p[i]);
            ans += ll(l1 - l2) * (r1 - i) * p[i];
            debug(l2);
        }

        if (r1 != n) {
            int r2 = find_rgt(r1, p[i]);
            debug(r2);
            ans += ll(r2 - r1) * (i - l1) * p[i];
        }
        debug(ans);
    }

    cout << ans << endl;
    return 0;
}
