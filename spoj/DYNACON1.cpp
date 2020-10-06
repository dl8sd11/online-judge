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
const ll MAXN = 1e5 + 5;

struct Node {
    Node *p = 0, *l = 0, *r = 0;
   int id = 0;
    Node (int _id) {
        id = _id;
    }
    bool rev = 0;
    bool isLeft () {
        return p && p->l == this;
    }
    bool isRight () {
        return p && p->r == this;
    }
    bool isRoot () {
        return !isLeft() && !isRight();
    }
    Node*& ch(bool c) {
        return c ? l : r;
    }
    void pull () {
    }
    void push () {
        if (rev) {
            swap(l, r);
            if (l) l->rev ^= 1;
            if (r) r->rev ^= 1;
            rev = 0;
        }

    }
    void rotate (bool c) {
        Node *x = ch(c);
        if (isLeft()) {
            p->l = x;
        }
        if (isRight()) {
            p->r = x;
        }
        x->p = p;

        ch(c) = x->ch(!c);
        if (ch(c)) {
            ch(c)->p = this;
        }

        x->ch(!c) = this;
        p = x;
        pull();
        x->pull();
    }
    void rotateTop() {
        p->rotate(isLeft());
    }
    void push_all () {
        if (!isRoot()) {
            p->push_all();
        }
        push();
    }
    void splay () {
        push_all();
        while (!isRoot()) {
            if (!p->isRoot()) {
                (isLeft() ^ p->isLeft() ? this : p)->rotateTop();
            }
            rotateTop();
        }
    }
    void access () {
        Node *x = this, *lst = nullptr;
        while (x) {
            x->splay();
            x->r = lst;
            lst = x;
            x = x->p;
        }
        splay();
    }
    void make_root () {
        access();
        rev ^= 1;
    }
    void link_to (Node *nd) {
        //print_chain();
        make_root();
        nd->access();
        nd->r = this;
        p = nd;
        p->pull();
        //print_chain();
    }

    void cut () {
        access();
        l->p = nullptr;
        l = nullptr;
        pull();
    }
    Node *get_min () {
        return l ? l->get_min() : this;
    }
    Node* get_root () {
        access();
        return get_min();
    }

    void print_splay (vector<int> &res) {
        if (l) l->print_splay(res);
        res.eb(id);
        if (r) r->print_splay(res);
    }

    void print_chain () {
        access();
        vector<int> res;
        print_splay(res);
        debug(res);
    }
} ;


Node *node[MAXN];
signed main () {
    TIME(main);
    IOS();

    int n, m;
    cin >> n >> m;
    for (int i=1; i<=n; i++) {
        node[i] = new Node(i);
    }
    while (m--) {
        string cmd;
        cin >> cmd;
        int u, v;
        cin >> u >> v;
        if (cmd[0] == 'a') {
            node[u]->link_to(node[v]);
        } else if (cmd[0] == 'r') {
            node[u]->make_root();
            node[v]->cut();
        } else {
            Node *ru = node[u]->get_root();
            Node *rv = node[v]->get_root();
            debug(ru->id, rv->id);
            cout << (ru == rv ? "YES" : "NO") << endl;
        }

    }

    return 0;
}

