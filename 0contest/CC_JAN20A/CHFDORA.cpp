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


struct Matrix {
    int n, m;
    int dt[MAXN];
    void trans () {
        Matrix tmp;
        tmp.n = m;
        tmp.m = n;
        REP (i, m) {
            REP (j, n) {
                tmp.get(i,j) = get(j,i);
            }
        }
        (*this) = tmp;
    }
    int &get (int x, int y) {
        return dt[x*m+y];
    }
} a, ta, px, py;

ostream& operator << (ostream &os, Matrix &ma) {
    os << "{" << endl;
    REP (i, ma.n) {
        REP (j, ma.m) {
            os << ma.get(i,j) << " ";
        }
        os << endl; 
    }
    return os << "}";
}

void buildPalindrome(Matrix &o,Matrix &ret) {
    ret.n = o.n, ret.m = o.m;
    int n = ret.n, m = ret.m;
    REP (i, n) {
        int bst = 0;
        ret.get(i,0) = 1;
        REP1 (j, m-1) {
            if (ret.get(i,bst)+bst>j) {
                ret.get(i,j) = min(bst+ret.get(i,bst)-j, ret.get(i,bst-(j-bst)));
            } else {
                ret.get(i,j) = 0;
            }
            while (j+ret.get(i,j)<m&&j-ret.get(i,j)>=0&&o.get(i,j-ret.get(i,j)) == o.get(i,j+ret.get(i,j))) {
                ret.get(i,j)++;
            }
            if (j+ret.get(i,j) >= bst+ret.get(i,bst)) {
                bst = j;
            }
        }
    }
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    int t;
    int n, m;

    cin >> t;
    while (t--) {
        #ifdef tmdd
        n = 1;
        m = 100000/n;
        #else
        cin >> n >> m;
        #endif
        a.n = n;
        a.m = m;

        REP (i, n) {
            REP (j, m) {
                #ifdef tmdd
                a.get(i,j) = rand() % 3;
                #else
                cin >> a.get(i, j);
                #endif
            }
        }
        ta = a;
        ta.trans();
        debug(a);
        debug(ta);

        buildPalindrome(a, px);
        buildPalindrome(ta, py);
        py.trans();
        debug(px);
        debug(py);

        ll ans = 0;
        REP (i, n) {
            REP (j, m) {
                ans += min(px.get(i,j), py.get(i,j));
            }
        }

        cout << ans << endl;
    }

    return 0;
}


/*
3
3 4
1 2 2 1
3 2 3 5
1 1 1 1

3 4
1 2 2 1
3 2 3 5
1 1 1 1

3 4
1 2 2 1
3 2 3 5
1 1 1 1
*/