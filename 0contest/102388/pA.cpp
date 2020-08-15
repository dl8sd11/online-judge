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
// const ll MAXN =

struct num{
    int a,b;
    num operator + (num B) {
        return {a+B.a,b+B.b};
    }
    num operator - (const num B) {
        return {a-B.a,b-B.b};
    }
    bool operator < (const num &B) const {
        return tie(a,b) < tie(B.a,B.b);
    }
    bool operator == (const num &B) const {
        return tie(a,b) == tie(B.a,B.b);
    }
};
ostream &operator << (ostream &_s,const num &_c){return _s<<'{'<<_c.a<<","<<_c.b<<"}";}
const int LIM = 10;
vector<num> pos[LIM];
vector<num> nos[LIM];
num pp[LIM], pn[LIM];
#define ALL(x) (x).begin(),(x).end()

vector<pair<int, num> > tblp, tbln;
vector<int> bin[LIM];

string int2str (int x) {
    string res;

    bool st = false;
    for (int i=LIM; i>=0; i--) {
        if ((1<<i) & x) {
            st = true;
        }
        if (st) res.push_back('0' + (1 & (x>>i)));
    }
    return res;
}
int main () {
    TIME(main);
    IOS();
    pos[0].pb({0});
    pp[0] = {2,0};
    pn[0] = {2,0};
    pp[1] = {1,1};
    pp[2] = {3,1};
    pn[2] = {3,-1};
    pn[1] = {-1,1};
    for (int i = 3; i<LIM; ++i) {
        pp[i] = pp[i-1] + pp [i-2] ;
        pn[i] = pn[i-2] - pn [i-1] ;
        debug ( pp [ i ] , pn [ i ] , i );
    }

    // bin[0].eb(0);
    for (int i = 0; i<LIM; ++i) {
        bin[i].pb(1<<i);
        for (int j = 0; j<i-1; ++j) {
            for (int nm : bin[j]) {
                bin[i] .pb (nm + (1<<i));
                bin[i] .pb (nm);
            }
        }
    }
    bin[LIM-1].pb(0);

    for (auto b : bin[LIM-1]) {
        {
            num cur = {0, 0};
            for (int i=0; i<LIM; i++) {
                if (b & (1<<i)) {
                    cur = cur + pp[i];
                }
            }
            tblp.eb(b, cur);
        }
        {
            num cur = {0, 0};

            bool flag = false;
            for (int i=0; i<LIM; i++) {
                if (b & (1<<i)) {
                    cur = cur + pn[i];
                    if (i == 0) {
                        flag = true;
                    }
                }
            }
            if (!flag) {
                tbln.eb(b, cur);
            }
        }
    }
    debug(tblp.size());

    map<num, int > st;

    for (auto p : tblp) {
        st[p.Y] = p.X;
        debug(p.Y, p.X);
    }

    // for (int i = 0; i<LIM; ++i) {
    //     num me = pp[i];
    //     for (int j = 0; j<i-1; ++j) {
    //         for (num nm : pos[j]) {
    //             pos[i] .pb (nm + me);
    //             pos[i] .pb (nm);
    //         }
    //     }
    //     sort(ALL(pos[i]));
    //     pos[i].resize(unique(ALL(pos[i])) - pos[i].begin());

    //     debug(pos[i].size());
    // }
    

    int t;
    cin >> t;
    

    while (t--) {
        int n;
        cin >> n;
        for (auto p : tbln) {
            num rem = {2*n - p.Y.a, -p.Y.b};
            if (st.count(rem)) {
                string bg = int2str(st[rem]);
                string ed = int2str(p.X);
                reverse(ALL(ed));
                ed = ed.substr(1);

                cout << bg << "." << ed << endl;
                break;
            }
        }
    }


    return 0;
}
