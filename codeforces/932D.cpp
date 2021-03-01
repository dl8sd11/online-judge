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
const int MAXN = 400005;
const int MAXLG = __lg(400005) + 3;

int q, last, cnt = 1, w[MAXN];
int anc[MAXLG][MAXN], mx[MAXLG][MAXN], seq[MAXLG][MAXN];
ll wsum[MAXLG][MAXN];

int fnd (int nd, int wt) {
    RREP (i, MAXLG-1) {
        if (mx[i][nd] < wt) {
            nd = anc[i][nd];
        }
    }
    return anc[0][nd];
}

void upd1 (int p) {
    REP1 (i, MAXLG-1) {
        anc[i][p] = anc[i-1][anc[i-1][p]];
        mx[i][p] = max(mx[i-1][p], mx[i-1][anc[i-1][p]]);
    }
}

void upd2 (int p) {
    REP1 (i, MAXLG-1) {
        seq[i][p] = seq[i-1][seq[i-1][p]];
        wsum[i][p] = wsum[i-1][p] + wsum[i-1][seq[i-1][p]];
    }
}

void add (int p) {
    anc[0][cnt] = p;
    mx[0][cnt] = w[p];
    upd1(cnt);
    seq[0][cnt] = fnd(cnt, w[cnt]);
    debug(seq[0][cnt]);
    wsum[0][cnt] = w[seq[0][cnt]];
    upd2(cnt);
}

int qry (int nd, ll sum) {
    if (w[nd] > sum) {
        return 0;
    } else {
        sum -= w[nd];
        int ret = 1;

        RREP (i, MAXLG-1) {
            if (seq[i][nd] != 0 && sum >= wsum[i][nd]) {
                ret += (1<<i);
                sum -= wsum[i][nd];
                nd = seq[i][nd];
            }
        }
        return ret;
    }
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> q;
    int tt = 0;
    REP1 (ts, q) {
        ll cmd, a, b;
        cin >> cmd >> a >> b;
        #ifndef tmd
        a ^= last, b ^= last;
        #endif
        debug(a, b);
        if (cmd == 1) {
            w[++cnt] = b;
            add(a);
        } else {
            int res = qry(a, b);
            last = res;
            cout << res << endl;
        }
    }
    return 0;
}

/*
100
1 1 10
1 2 1
1 3 1
1 4 9
1 5 6

100
1 1 1
1 2 0
1 3 0
1 4 0
*/