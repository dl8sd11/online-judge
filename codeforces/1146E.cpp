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
const ll MAXN = 100005;

int n, q, a[MAXN];
int res[MAXN*2+5];
vector<int> gt, lt;

struct Treap {
    Treap *l, *r;
    int tag, val, sz, pri;
    bool rev;

    void push () {
        if (tag != 0) {
            if (l) {
                l->tag = tag;
            }
            if (r) {
                r->tag = tag;
            }
            val = tag;
            tag = 0;
        }
        if (rev) {
            swap(l, r);
            if (l) {
                l->rev ^= 1;
            }
            if (r) {
                r->rev ^= 1;
            }
            rev = 0;
        }
    }

    void pull () {
        sz = 1;
        if (l) {
            sz += l->sz;
        }
        if (r) {
            sz += r->sz;
        }
    }

    Treap () {
        l = r = nullptr;
        tag = val = 0;
        sz = 1;
        pri = rand();
        rev = 0;
    }

};

Treap *mrg (Treap *a, Treap *b) {
    if (!a || !b) {
        return a ? a : b;
    } else {
        if (a->pri > b->pri) {
            a->push();
            a->r = mrg(a->r, b);
            a->pull();
            return a;
        } else {
            b->push();
            b->l = mrg(a, b->l);
            b->pull();
            return b;
        }
    }
}


int SIZ (Treap *o) {
    return o ? o->sz : 0;
}

void split (Treap *o, Treap *&a, Treap *& b, int sz) {
    if (!o) {
        a = b = nullptr;
        return;
    } else {
        o->push();
        if (SIZ(o->l) < sz) {
            a = o;
            split(a->r, a->r, b, sz - SIZ(o->l) - 1);
        } else {
            b = o;
            split(b->l, a, b->l, sz);
        }
        o->pull();
    }
}

int conv (int x) {
    return x + MAXN;
}

Treap *root;
void build () {
    root = new Treap();
    REP (i, MAXN*2) {
        root = mrg(root, new Treap());
    }
}

int cnt;
void dfs (Treap *nd) {
    nd->push();
    if (nd->l) {
        dfs(nd->l);
    }
    res[cnt++] = nd->val;
    if (nd->r) {
        dfs(nd->r);
    }
}

void chg (int l, int r, int v) {
    debug(l-MAXN, r-MAXN, v);
    Treap *a, *b, *c;
    split(root, a, b, l);
    split(b, b, c, r-l);
    b->tag = v;
    assert(b->sz == r-l);
    root = mrg(a, mrg(b, c));
}

void flip (int l, int r) {
    debug(l-MAXN, r-MAXN);
    Treap *a, *b, *c;
    split(root, a, b, l);
    split(b, b, c, r-l);
    b->rev ^= 1;
    assert(b->sz == r-l);
    root = mrg(a, mrg(b, c));
}
// void chg (int l, int r, int v) {
//     debug(l-MAXN, r-MAXN, v);
//     for (int i=l; i<r; i++) {
//         res[i] = v;
//     }
// }

// void flip (int l, int r) {
//     debug(l-MAXN, r-MAXN);
//     vector<int> el;
//     for (int i=l; i<r; i++) {
//         el.eb(res[i]);
//     }
//     reverse(ALL(el));

//     for (int i=l; i<r; i++) {
//         res[i] = el[i-l];
//     }
// }
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    srand(time(0));
    build();

    cin >> n >> q;
    REP (i, n) {
        cin >> a[i];
    }
    while (q--) {
        char s;
        int x;
        cin >> s >> x;

        if (s == '<') {
            lt.eb(x);
            if (x <= 0) {
                chg(0, conv(x), -1);
                chg(conv(-x+1), MAXN*2+1, 1);
            } else {
                x--;
                chg(0, conv(-x), -1);
                chg(conv(x+1), MAXN*2+1, 1);
                flip(conv(-x), conv(x+1));
            }
        } else {
            gt.eb(x);
            if (x >= 0) {
                chg(0, conv(-x), 1);
                chg(conv(x+1), MAXN*2+1, -1);
            } else {
                x++;
                chg(0, conv(x), 1);
                chg(conv(-x+1), MAXN*2+1, -1);
                flip(conv(x), conv(-x+1));
            }
        }
    }

    dfs(root);

    sort(ALL(lt));
    sort(ALL(gt));
    REP (i, n) {
        if (res[conv(a[i])] == 0) {
            int ans = 0;
            ans += lt.end() - upper_bound(ALL(lt), abs(a[i]));
            ans += lower_bound(ALL(gt), -abs(a[i])) - gt.begin();

            cout << a[i] * ((ans&1) ? -1 : 1) << " \n"[i==n-1];
        } else {
            assert(res[conv(-a[i])] == -res[conv(a[i])]);
            cout << res[conv(a[i])] * a[i] << " \n"[i==n-1];
        }
    }

    return 0;
}
