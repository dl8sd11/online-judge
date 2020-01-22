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
const ll MAXN = 1000006;

int h, w, hw;
int p[MAXN*3];
pair<int,int> pos[MAXN];

int pid (int x, int y) {
    return x * (w+2) + y;
}

pair<int,int> seg[MAXN*4];
int tag[MAXN*4];

pair<int,int> mrg (pii l, pii r) {
    if (l.X > r.X) {
        swap(l, r);
    }
    if (l.X == r.X) {
        return {l.X, l.Y + r.Y};
    } else {
        return l;
    }
}

void push (int o) {
    if (tag[o] != 0) {
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        seg[o].X += tag[o];
        tag[o] = 0;
    }
}

pii get (int o) {
    if (tag[o] != 0) {
        return {seg[o].X+tag[o], seg[o].Y};
    } else {
        return seg[o];
    }
}

void pull (int o) {
    seg[o] = mrg(get(o<<1), get(o<<1|1));
}

void build_seg (int o, int l, int r) {
    if (r == l + 1) {
        seg[o] = {0, 1};
    } else {
        int mid = (l + r ) >> 1;
        build_seg(o<<1, l, mid);
        build_seg(o<<1|1, mid, r);
        pull(o);
    }
}

pair<int,int> qry (int qL, int qR, int o, int nL, int nR) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return {iNF, 0};
    } else if (qL <= nL && nR <= qR) {
        return get(o);
    } else {
        push(o);
        int mid = (nL + nR) >> 1;
        return mrg(qry(qL, qR, o<<1, nL, mid),
                    qry(qL, qR, o<<1|1, mid, nR));
    }
}

void add (int qL, int qR, int val, int o, int nL, int nR) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] += val;
    } else {
        push(o);
        int mid = (nL + nR) >> 1;
        add(qL, qR, val, o<<1, nL, mid);
        add(qL, qR, val, o<<1|1, mid, nR);
        pull(o);
    }
}

void make (int x, int y, int val) {
    vector<int> tm = {p[pid(x,y)], p[pid(x+1,y)], p[pid(x,y+1)], p[pid(x+1,y+1)]};
    sort(ALL(tm));

    debug(x, y);
    debug(tm[0], tm[1], val);
    debug(tm[2], tm[3], val);
    add(tm[0], tm[1], val, 1, 1, hw);
    add(tm[2], tm[3], val, 1, 1, hw);
}



void rst (int x, int y) {
    make(x, y, -1);
    make(x-1, y, -1);
    make(x, y-1, -1);
    make(x-1, y-1, -1);
    p[pid(x,y)] = h*w + 1;
    make(x, y, 1);
    make(x-1, y, 1);
    make(x, y-1, 1);
    make(x-1, y-1, 1);
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> h >> w;
    hw = h*w + 1;

    fill(p, p+MAXN*3, h*w+1);
    REP1 (i, h) {
        REP1 (j, w) {
            int x;
            cin >> x;
            p[pid(i,j)] = x;
            pos[x] = {i, j};
        }
    }

    build_seg(1, 1, hw);

    REP (i, h+1) {
        REP (j, w+1) {
            make(i,j, 1);
        }
    }

    ll ans = 0;
    REP1 (i, h*w) {
        pii res = qry(i,hw, 1, 1, hw);
        debug(res);
        if (res.X == 4) {
            ans += res.Y;
        }
        rst(pos[i].X, pos[i].Y);
    }

    cout << ans << endl;
    return 0;
}
