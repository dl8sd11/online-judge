#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double, double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) static_cast<int>(i.size())
#define FOR(i, j, k, in) for (int i=j; i < (k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j; i >= (k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i, j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(), _a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
template<typename T, typename S>
istream &operator >> (istream &is, pair<T, S> &p) {
    return is >> p.X >> p.Y;
}
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do {\
    fprintf(stderr, "%s - %d (%s) = ", __PRETTY_FUNCTION__, __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T> void _do(T &&_x) {cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x, S &&..._t) {cerr <<_x <<" ,"; _do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s, const pair<_a, _b> &_p) {return _s << "(" << _p.X << "," << _p.Y << ")";}
template<typename It> ostream& _OUTC(ostream &_s, It _ita, It _itb)
{
    _s << "{";
    for (It _it=_ita; _it != _itb; _it++) {
        _s <<(_it == _ita?"":",")<< *_it;
    }
    _s << "}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s, const vector<_a> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,2> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,3> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,4> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,5> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const set<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const deque<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s, const map<_a,_b> &_c) {return _OUTC(_s,ALL(_c));}
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
const ll MAXN = 2e5 + 5;
const int maxn = 100005;


//}}}
ll mypow(ll a,ll b){
	ll res=1LL;
	while(b){
		if(b&1) res=res*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return res;
}

int seg[maxn*4], tag[maxn*4], mn[maxn*4];

void push (int o) {
    if (tag[o]) {
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        mn[o] += tag[o];
        tag[o] = 0;
    }
}

int get (int o) {
    return mn[o] + tag[o];
}

void pull (int o) {
    mn[o] = min(get(o<<1), get(o<<1|1));
}

int n, m, q;
void add (int qL, int qR, int val, int o, int nL, int nR) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        debug(o, nL, nR, val);
        tag[o] += val;
        debug(get(o));
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        add(qL, qR, val, o<<1, nL, nM);
        add(qL, qR, val, o<<1|1, nM, nR);
        pull(o);
    }
}

void add (int qL, int qR, int val) {
    debug(qL, qR, val);
    add(qL, qR, val, 1, 0, m);
}

int qone (int x, int o=1, int nL=0, int nR=m) {
    if (nL == nR - 1) {
        return get(o);
    } else {
        int nM = (nL + nR) >> 1;
        if (x >=  nM) {
            return tag[o] + qone(x, o<<1|1, nM, nR);
        } else {
            return tag[o] + qone(x, o<<1, nL, nM);
        }
    }
}

int qry () {
    debug(mn[1], tag[1]);
    return get(1);
}

void build (int o, int l, int r) {
    if (r == l + 1) {
        mn[o] = seg[l];
    } else {
        int M = (l + r) >> 1;
        build(o<<1, l, M);
        build(o<<1|1, M, r);
        pull(o);
    }
}

void build () {
    build(1, 0, m);
}
int main(){
	IOS();
    cin >> n >> m >> q;
    vector<int> a(n);

    int ip = 0; // 0 - indexed
    for (int i=0; i<n; i++) {
        cin >> a[i];
        if (a[i] < a[0]) {
            ip++;
        }
    }
	
    vector<int> x(m), y(m);
    vector<vector<int> > b(m);

    memset(seg, 0x3f, sizeof(seg));
    for (int i=0; i<m; i++) {
        int r, d;
        cin >> r;
        for (int j=0; j<r; j++) {
            cin >> d;
            b[i].eb(d);
            if (d > a[0]) {
                y[i]++;
            }
        }
        x[i] = r;
        seg[i] = ip + 1 - r;
    }


    build();
    for (int X=0; X<m; X++) {
        add(X+1, m, -y[X]);
    }

    for (int i=0; i<q; i++) {
        int X, Y, Z;
        cin >> X >> Y >> Z;
        X--;
        Y--;
        add(X+1, m, y[X]);
        y[X] -= (b[X][Y] > a[0]);
        b[X][Y] = Z;
        y[X] += (b[X][Y] > a[0]);
        add(X+1, m, -y[X]);

        cout << (qry() > 0) << endl;
    }

	return 0;
}
