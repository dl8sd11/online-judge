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
// const ll MAXN = 

struct Node {
    Node *l, *r;
    int val, sz, pri;
    bool rev;

    Node (int v) {
        l = r = nullptr;
        val = v;
        sz = 1;
        rev = false;
        pri = rand();
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

    void push () {
        if (rev) {
            if (l) {
                l->rev ^= 1;
            }
            if (r) {
                r->rev ^= 1;
            }
            swap(l, r);
            rev = 0;
        }
    }
};
Node *root;

Node *mrg (Node *a, Node *b) {
    if (!a || !b) {
        return a ? a : b;
    }
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

int SIZ (Node *nd) {
    return nd ? nd->sz : 0;
}

void split (Node *o, Node *&a, Node *&b, int k) {
    if (!o) {
        a = b = nullptr;
        return;
    } else {
        o->push();
        if (SIZ(o->l) + 1 <= k) {
            a = o;
            split(o->r, a->r, b, k-SIZ(o->l)-1);
        } else {
            b = o;
            split(o->l, a, b->l, k);
        }
        o->pull();
    }
}

void flip (int l, int r) {
    Node *nL, *nM, *nR;

    split(root, nL, nM, l-1);
    split(nM, nM, nR, r-l+1);
    assert(SIZ(nM) == r-l+1);
    if (nM) {
        nM->rev ^= 1;
    }
    root = mrg(mrg(nL, nM), nR);
}

vector<int> ans;
void dfs (Node *nd) {
    nd->push();
    if (nd->l) {
        dfs(nd->l);
    }
    ans.eb(nd->val);
    if (nd->r) {
        dfs(nd->r);
    }
}
int n, m;
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    srand(time(0));

    while (cin >> n >> m) {
        REP1 (i, n) {
            if (i == 1) {
                root = new Node(i);
            } else {
                root = mrg(root, new Node(i));
            }
        }
        while (m--) {
            int l, r;
            cin >> l >> r;
            flip(l, r);
        }

        ans.clear();
        dfs(root);
        REP (i, n) {
            cout << ans[i] << " \n"[i==n-1];
        }

    }


    return 0;
}
