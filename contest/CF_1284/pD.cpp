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

int n;

struct Data {
    pair<int,int> a, b;
}sa[MAXN], sb[MAXN];

bool sort_by_l (const Data &d1, const Data &d2) {
    return d1.a.X < d2.a.X;
}

bool sort_by_r (const Data &d1, const Data &d2) {
    return d1.a.Y < d2.a.Y;
}

vector<int> val;

void dis (int &x) {
    x = lower_bound(ALL(val),x)-val.begin()+1;
}

const int MAXC = 400005;

int seg[MAXC*4], tag[MAXC*4];

void push (int o) {
    if (tag[o]) {
        seg[o] += tag[o];
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        tag[o] = 0;
    }
}

int get (int o) {
    return seg[o] + tag[o];
}

void pull (int o) {
    seg[o] = max(get(o<<1), get(o<<1|1));
}

void add (int qL, int qR, int v, int o,int nL, int nR) {
    if (qL >= qR || qL >= nR || qR <= nL) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] += v;
    } else {
        int nM = (nL + nR) >> 1;
        push(o);
        add(qL, qR, v, o<<1, nL, nM);
        add(qL, qR, v, o<<1|1, nM, nR);
        pull(o);
    }
}

int qry (int qL, int qR, int o,int nL, int nR) {
    if (qL >= qR || qL >= nR || qR <= nL) {
        return 0;
    } else if (qL <= nL && nR <= qR) {
        return get(o);
    } else {
        int nM = (nL + nR) >> 1;
        push(o);
        return max(qry(qL, qR, o<<1, nL, nM),\
        qry(qL, qR, o<<1|1, nM, nR));
    }
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> sa[i].a.X >> sa[i].a.Y;
        cin >> sa[i].b.X >> sa[i].b.Y;
        val.emplace_back(sa[i].a.X);
        val.emplace_back(sa[i].a.Y);
        val.emplace_back(sa[i].b.X);
        val.emplace_back(sa[i].b.Y);
    }

    sort(ALL(val));
    val.resize(unique(ALL(val))-val.begin());
    REP (i, n) {
        dis(sa[i].a.X);
        dis(sa[i].a.Y);
        dis(sa[i].b.X);
        dis(sa[i].b.Y);
    }


    int fail = false;

    REP (u, 2) {
        MEM(seg, 0);
        MEM(tag, 0);
        REP (i, n) {
            swap(sa[i].a, sa[i].b);
            sb[i] = sa[i];
        }

        sort(sa,sa+n, sort_by_r);
        sort(sb,sb+n, sort_by_l);
        
        int ida = 0;
        REP (i, n) {
            while (ida<n && sa[ida].a.Y < sb[i].a.X) {
                add(sa[ida].b.X,sa[ida].b.Y+1,1,1,0,MAXC);
                ida++;
            }

            if (qry(sb[i].b.X, sb[i].b.Y+1,1,0,MAXC) > 0) {
                fail = true;
            }
        }

    }
    

    cout << (fail ? "NO" : "YES") << endl;
    return 0;
}
