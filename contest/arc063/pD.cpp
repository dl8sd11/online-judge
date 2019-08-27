#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
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

namespace SEG {
    int seg[MAXN * 4], tag[MAXN * 4];

    int get (int o) {
        return seg[o] + tag[o];
    }

    void pull (int o) {
        seg[o] = max(get(o<<1), get(o<<1|1));
    }

    void push (int o) {
        if (tag[o]) {
            seg[o] = get(o);
            tag[o<<1] += tag[o];
            tag[o<<1|1] += tag[o];
            tag[o] = 0;
        }
    }

    void build () {
        MEM(seg, 0);
        MEM(tag, 0);
    }

    void add (int qL, int qR, int val, int o, int nL, int nR) {
        if (qL >= nR || qR <= nL || qL >= qR) {
            return;
        } else if (qL <= nL && nR <= qR) {
            tag[o] += val;
        } else {
            int nM = (nL + nR) >> 1;
            push(o);
            add(qL, qR, val, o<<1, nL, nM);
            add(qL, qR, val, o<<1|1, nM, nR);
            pull(o);
        }
    }

    int qry (int qL, int qR, int o, int nL, int nR) {
        if (qL >= nR || qR <= nL || qL >= qR) {
            return 0;
        } else if (qL <= nL && nR <= qR) {
            return get(o);
        } else {
            int nM = (nL + nR) >> 1;
            push(o);
            return max(qry(qL, qR, o<<1, nL, nM), qry(qL, qR, o<<1|1, nM, nR));
        }
    }
}
int w, h, n, nn, x[MAXN], y[MAXN];

struct Line {
    int y;
    int l, r;
    
    void init (int yin) {
        y = yin;
        l = 0, r = w;
    }

    void add (int xx) {
        if (xx >= (w+1)/2) {
            r = min(r, xx);
        } else {
            l = max(l, xx);
        }
    }
} line[MAXN];

void build_line () {
    vector<int> val;
    REP (i, n) {
        val.eb(y[i]);
    }

    val.eb(0);
    val.eb(h);
    sort(ALL(val));
    val.resize(unique(ALL(val)) - val.begin());
    nn = SZ(val);

    REP (i, nn) {
        line[i].init(val[i]);
    }

    REP (i, n) {
        int lnid = lower_bound(ALL(val), y[i]) - val.begin();
        line[lnid].add(x[i]);
    }
}

int solve () {
    vector<pii> lstk, rstk;
    SEG::build();

    int ans = 0;
    REP (i, nn) {
        auto cur = line[i];
        debug(cur.y);
        if (i) {
#ifdef tmd
            int l = 0, r = w, bst = -iNF;
            REP (j, i) {
                l = 0, r = w;
                for (int k=j+1; k<i; k++) {
                    l = max(l, line[k].l);
                    r = min(r, line[k].r);
                }
                bst = max(bst, (r - l) * 2 - line[j].y * 2);
            }
            bst += cur.y * 2;
            if (bst != SEG::qry(0, i, 1, 0, nn) * 2 + cur.y * 2) {
                debug(i);
                debug(bst , SEG::qry(0, i, 1, 0, nn) * 2 + cur.y * 2);
            }

#endif
            ans = max(ans, SEG::qry(0, i, 1, 0, nn) * 2 + cur.y * 2);
        }
        while (!lstk.empty() && lstk.back().X <= cur.l) {
            pii gb = lstk.back();
            lstk.pop_back();

            int lst = lstk.empty() ? 0: lstk.back().Y + 1;
            SEG::add(lst, gb.Y + 1, gb.X - cur.l, 1, 0, nn);
        }
        lstk.eb(cur.l, i - 1);
        lstk.eb(0, i);
        
        while (!rstk.empty() && rstk.back().X >= cur.r) {
            pii gb = rstk.back();
            rstk.pop_back();

            int lst = rstk.empty() ? 0: rstk.back().Y + 1;
            SEG::add(lst, gb.Y + 1, cur.r - gb.X, 1, 0, nn);
        }
        rstk.eb(cur.r, i - 1);
        rstk.eb(w, i);

        SEG::add(i, i + 1, w - line[i].y, 1, 0, nn);

    }

    return ans;
}

/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    cin >> w >> h >> n;
    REP (i, n) {
        cin >> x[i] >> y[i];
    }
    

    // if (n == 1) {
    //     cout << max(max(x[0], w - x[0]) + h, w + max(y[0], h - y[0])) * 2 << endl;
    //     return 0;
    // }
    int ans = 0;

    build_line();
    ans = max(ans, solve());

    swap(w, h);
    REP (i, n) {
        swap(x[i], y[i]);
    }

    build_line();
    ans = max(ans, solve());

    cout << ans << endl;
    return 0;
}
