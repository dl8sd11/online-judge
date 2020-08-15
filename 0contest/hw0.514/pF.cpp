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
const ll MAXN = 500005;

int sq[MAXN];
struct DC {
    vector<int> val;
    vector<double> ans;
    vector<int> pos;

    DC (vector<int> v) : val(v), ans(SZ(v),0), pos(SZ(v))  {
    }

    void solve (int qL, int qR, int tL, int tR) {
        if (qL >= qR) {
            return;
        }
        int qM = (qL + qR) >> 1;
        for (int i=max(0,tL); i<=min(tR, qM); i++) {
            double cur = val[i] + sqrt(abs(i-qM));
            if (cur > ans[qM]) {
                ans[qM] = cur;
                pos[qM] = i;
            }

        }
        solve(qL, qM, tL, pos[qM]);
        solve(qM+1, qR, pos[qM], tR);
    }
};
int main () {
    TIME(main);
    IOS();

    for (int i=0; i*i <=MAXN; i++) {
        for (int j=i*i+1; j<=(i+1)*(i+1); j++) {
            if (j >= MAXN) {
                break;
            }
            sq[j] = i+1;
        }
    }
    pary(sq, sq+10);
    int n;
    cin >> n;

    vector<int> v(n);
    srand(time(0));
    for (int i=0; i<n; i++) {
#ifdef tmd
        v[i] = rand() % n + 1;
#else
       cin >> v[i]; 
#endif
    }
    
    DC pre(v);
    reverse(ALL(v));
    DC suf(v);
    reverse(ALL(v));
    pre.solve(0, n, 0, n-1);
    suf.solve(0, n, 0, n-1);

    debug(suf.ans);
    debug(suf.pos);
    debug(suf.val);

    reverse(ALL(suf.ans));
    reverse(ALL(suf.pos));

    debug(pre.ans);
    debug(pre.pos);

    vector<int> ans(n);
    for (int i=0; i<n; i++) {
        ans[i] = max(0, int(ceil(max(pre.ans[i], suf.ans[i]))) - v[i]);
        cout << ans[i] << endl;
    }

    debug(v);
    debug(ans);
#ifdef tmd
    vector<int> bf(n);
    for (int i=0; i<n; i++) {
        int mx = 0;
        for (int j=0; j<n; j++) {
            mx = max(mx, v[j] + sq[abs(i-j)]);
        }
        bf[i] = max(0, mx - v[i]);
    }
    debug(bf);
    assert(ans == bf);


#endif

    return 0;
}
