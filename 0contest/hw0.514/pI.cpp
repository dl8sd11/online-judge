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
const ll MAXN = 200005;

int n;
struct Result {
    int score, country;
} res[2][MAXN];

int seg[MAXN*4], tag[MAXN*4];

int get (int o) {
    return seg[o] + tag[o];
}

void push (int o) {
    if (tag[o]) {
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        seg[o] += tag[o];
        tag[o] = 0;
    }
}

void pull (int o) {
    seg[o] = min(get(o<<1), get(o<<1|1));
}

void build (int o, int nL, int nR) {
    if (nL == nR - 1) {
        seg[o] = n - nL;
    } else {
        int nM = (nL + nR) >> 1;
        build(o<<1, nL, nM);
        build(o<<1|1, nM, nR);
        pull(o);
    }
}

void add (int qR, int val, int o, int nL, int nR) {
    if (qR < nL) {
        return;
    } else if (nR <= qR + 1) {
        tag[o] += val;
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        add(qR, val, o<<1, nL, nM);
        add(qR, val, o<<1|1, nM, nR);
        pull(o);
    }
}

int qry () {
    return get(1);
}

vector<int> cnt[MAXN];
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP (i, 2) {
        for (int j=n-1; j>=0; j--) {
            cin >> res[i][j].country >> res[i][j].score;
        }
    }

    build(1, 0, n);

    cnt[res[1][n-1].country].eb(n-1);

    int ans = 0;
    for (int i=n-1, ptr=n-1; i>=0; i--) {
        while (ptr>0 && res[1][ptr-1].score >= res[0][i].score) {
            ptr--;
            cnt[res[1][ptr].country].eb(ptr);
        }
        int cc = res[0][i].country;
        if (cnt[cc].size()) {
            int mat = cnt[cc].back();
            add(mat, -1, 1, 0, n);
            debug(mat, qry());
            if (qry() < 0) {
                add(mat, 1, 1, 0, n);
                ans++;
                add(ptr, -1, 1, 0, n);
            } else {
                cnt[cc].pop_back();
            }
        } else {
            add(ptr, -1, 1, 0, n);
            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}
