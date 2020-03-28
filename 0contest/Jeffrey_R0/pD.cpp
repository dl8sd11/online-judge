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
const ll MAXN = 100005;

int n, m, q;
int seg[MAXN*2];

int pos[MAXN], dir[MAXN];
pair<int,int> shark[MAXN];
pair<int,int> sort_fish[MAXN];

int ans[MAXN];

void build () {
    REP (i, n) {
        seg[i+n] = sort_fish[i].X;
    }
}

int qry (int x) {
    int res = 0;
    for (x+=n; x>0; x>>=1) {
        res += seg[x];
    }
    return res;
}

void add (int l, int r, int val) {
    for  (l+=n, r+=n; l<r; l>>=1, r>>=1) {
        if (l&1) {
            seg[l++] += val;
        }
        if (r&1) {
            seg[--r] += val;
        }
    }
}

int main () {
    TIME(main);
    IOS();

    cin >> n >> m >> q;
    REP (i, n) {
        cin >> pos[i];
        char c;
        cin >> c;
        dir[i] = c == 'R' ? 1 : -1;
    }

    REP (i, q) {
        cin >> shark[i].X >> shark[i].Y;
    }
    shark[q].X = m;

    REP (i, n) {
        pos[i] += dir[i] * shark[0].X;
        sort_fish[i] = {pos[i], i};
    }
    sort(sort_fish, sort_fish+n);

    build();

    REP (i, q) {
        int L = -1, R = n;
        while (L < R - 1) {
            int M = (L + R) >> 1;
            if (qry(M) > shark[i].Y) {
                R = M;
            } else {
                L = M;
            }
        }

        int dtime = shark[i+1].X - shark[i].X;
        add(0, L+1, -dtime);
        add(R, n, dtime);
    }

    REP (i, n) {
        ans[sort_fish[i].Y] = qry(i);
    }

    REP (i, n) {
        cout << ans[i] << " \n"[i==n-1];
    }
    return 0;
}
