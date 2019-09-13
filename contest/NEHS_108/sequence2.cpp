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
const ll MAXN = 300005;

typedef array<array<int,5>,5> a55;

int n, q, k, a[MAXN];
a55 seg[MAXN*8];
int tag[MAXN*8], len[MAXN*8];
bool leg[5][5];


a55 mrg (const a55 &l, const a55 &r) {
    a55 ret = {};
    REP (i, 5) {
        REP (j, 5) {
            ret[i][j] = max(l[i][j], r[i][j]);
            REP (x, 5) {
                REP (y, 5) {
                    if (leg[x][y] && l[i][x] && r[y][j]) {
                        ret[i][j] = max(ret[i][j], l[i][x]+ r[y][j]);
                    }
                }
            }
        }
    }
    return ret;
}


void push (int o) {
    if (tag[o] != -1) {
        seg[o] = {};
        seg[o][tag[o]][tag[o]] = leg[tag[o]][tag[o]] ? len[o] : 1;
        tag[o<<1] = tag[o];
        tag[o<<1|1] = tag[o];
        tag[o] = -1;
    }
}

void pull (int o) {
    push(o<<1);
    push(o<<1|1);
    seg[o] = mrg(seg[o<<1], seg[o<<1|1]);
}

void build (int o = 1, int l = 0, int r = n) {
    len[o] = r - l;
    if (r == l + 1) {
        seg[o] = {};
        seg[o][a[l]][a[l]] = 1;
        tag[o] = -1;
    } else {
        int mid = (l + r) >> 1;
        tag[o] = -1;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        pull(o);
    }
}

void chg (int qL, int qR, int val, int o = 1, int nL = 0, int nR = n) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] = val;
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        chg(qL, qR, val, o<<1, nL, nM);
        chg(qL, qR, val, o<<1|1, nM, nR);
        pull(o);
    }
}

a55 qry (int qL, int qR, int o = 1, int nL = 0, int nR = n) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return {};
    } else if (qL <= nL && nR <= qR) {
        push(o);
        return seg[o];
    } else {
        push(o);
        int nM = (nL + nR) >> 1;
        return mrg(qry(qL, qR, o<<1, nL, nM), qry(qL, qR, o<<1|1, nM, nR));
    }
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> k >> q;
    REP (i, n) {
        cin >> a[i];
    }
    REP (i, k) {
        int f, t;
        cin >> f >> t;
        leg[f][t] = true;
    }

    build();

    #ifdef tmd
    REP (i, 5) {
        REP (j, 5) {
            cout << seg[3][i][j] << " \n"[j==4];
        }
    }
    #endif
    

    while (q--) {
        char c;
        int l, r, x;
        cin >> c >> l >> r;
        l--, r--;
        if (c == 'Q') {
            a55 res = qry(l, r+1);
            int ret = 0;
            REP (i, 5) {
                REP (j, 5) {
                    ret = max(ret, res[i][j]);
                }
            }
            cout << ret << endl;
        } else {
            cin >> x;
            chg(l, r+1, x);
            #ifdef tmdd
            REP (i, 5) {
                REP (j, 5) {
                    cout << seg[3][i][j] << " \n"[j==4];
                }
            }
            #endif
        }
    }

    return 0;
}

/*
6 4 6
0 1 2 2 1 0
0 1
1 2
2 1
1 0
Q 1 6
M 3 4 1
Q 1 6
Q 2 5
M 3 4 0
Q 1 6
*/
