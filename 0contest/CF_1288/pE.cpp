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
const ll MAXN = 300005;

int n, m, a[MAXN];


int bbit[MAXN], amn[MAXN], amx[MAXN], dif[MAXN];

void badd (int x, int val, int *bit) {
    for (x++;x<MAXN;x+=-x&x) {
        bit[x] += val;
    }
}

int bqry (int x, int *bit) {
    int ret = 0;
    for (x++;x>0;x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int slst[MAXN];

vector<pair<int,int> > query[MAXN];
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> m;
    REP (i, m) {
        cin >> a[i];
    }

    REP1 (i, n) {
        amn[i] = i;
        amx[i] = i;
    }

    MEM(slst, -1);
    REP (i, m) {
        if (slst[a[i]] == -1) {
            amn[a[i]] = 1;
            amx[a[i]] = max(amx[a[i]], a[i]+bqry(n,bbit)-bqry(a[i],bbit));
            badd(a[i], 1, bbit);
        } else {
            query[slst[a[i]]].emplace_back(i, a[i]);
        }
        slst[a[i]] = i;
    }

    REP1 (i, n) {
        if (slst[i] == -1) {
            amx[i] = max(amx[i], i+bqry(n,bbit)-bqry(i,bbit));
        } else {
            debug(slst[i], m);
            query[slst[i]].emplace_back(m, i);
        }
    }

    MEM(slst, -1);
    for (int i=m-1;i>=0;i--) {
        debug(i, a[i]);
        if (slst[a[i]] != -1) {
            badd(slst[a[i]], -1, dif);
            badd(i, 1, dif);
        } else {
            badd(i, 1, dif);
        }
        slst[a[i]] = i;
        for (auto q : query[i]) {
            amx[q.Y] = max(amx[q.Y], bqry(q.X, dif));
        }
    }
    

    REP1 (i, n) {
        cout << amn[i] << " " << amx[i] << endl;
    }


    return 0;
}

/*
5 7
2 3 1 2 1 3 4
*/
