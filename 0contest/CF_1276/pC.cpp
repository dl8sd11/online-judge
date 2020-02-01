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
const int MAXN = 400005;

int n, res[MAXN];
map<int,int> cnt;
int pre[MAXN], pcnt[MAXN];
int N, M;

int toId (int x, int y) {
    return x * M + y;
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    int x = 1577242548;
    srand(x);
    debug(x);

    cin >> n;
    REP (i, n) {
        int d;
        #ifdef tmdd
        d = rand() % 5 + 1;
        #else
        cin >> d;
        #endif
        cnt[d]++;
    }

    for (auto p : cnt) {
        pre[p.Y] += p.Y;
        pcnt[p.Y]++;
    }
    REP1 (i, MAXN-1) {
        pre[i] += pre[i-1];
        pcnt[i] += pcnt[i-1];
    }

    pair<int,int> bst;
    for (int i=1;i*i<=n;i++) {
        int sum = n - (pre[MAXN-1] - pre[i]) + (pcnt[MAXN-1] - pcnt[i]) * i;
        int j = sum / i;
        if (i <= j && i * j > bst.X * bst.Y) {
            bst.X = i;
            bst.Y = j;
        }
    }   

    debug(bst);
    tie(N, M) = bst;

    int id = 0;

    vector<pair<int,int> > vec;
    for (auto p : cnt) {
        vec.emplace_back(p.Y, p.X);
    }
    sort(ALL(vec));

    for (auto it=vec.rbegin(); it!=vec.rend(); it++) {
        REP (i, min(N, it->first)) {
            int blk = id / N;
            int x = id % N;
            int y = (blk + id % N) % M;
            debug(*it, x, y);
            res[toId(x, y)] = it->second;
            id++;
        }
    }

    cout << N * M << endl;
    cout << N << " " << M << endl;
    REP (i, N) {
        REP (j, M) {
            cout << res[toId(i, j)] << " \n"[j==M-1];
        }
    }

    REP (i, N) {
        set<int> row;
        REP (j, M) {
            row.insert(res[toId(i, j)]);
        }
        assert(row.count(0) == false);
        assert(row.size() == M);
    }

    REP (j, M) {
        set<int> row;
        REP (i, N) {
            row.insert(res[toId(i, j)]);
        }
        assert(row.count(0) == false);
        assert(row.size() == N);
    }


    return 0;
}
