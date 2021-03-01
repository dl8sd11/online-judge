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

struct Robot {
    int x, r, q, qid;
} rbt[MAXN];
int n, k;
ll ans;
vector<int> qval;

struct Treap {
    struct Node {
        Node *l, *r;
        int pri, sz;
        pii key;
        Node (int x, int id  ) {
            l = r =nullptr;
            pri = rand();
            sz = 1;
            key = pii(x, id);
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
    };
    Node *root;

    int SIZ (Node *a) {
        return a ? a->sz : 0;
    }
    Node *mrg (Node *a, Node *b) {
        if (!a || !b) {
            return a ? a : b;
        }
        if (a->pri > b->pri) {
            a->r = mrg(a->r, b);
            a->pull();
            return a;
        } else {
            b->l = mrg(a, b->l);
            b->pull();
            return b;
        }
    }

    void split (Node *o, Node *&a, Node *&b, pii sp) {
        if (!o) {
            a = b = nullptr;
            return;
        } else {
            if (o->key >= sp) {
                b = o;
                split(b->l, a, b->l, sp);
            } else {
                a = o;
                split(a->r, a->r, b, sp);
            }
            o->pull();
        }
    }

    void era (int x, int id) {
        Node *l, *m, *r;
        split(root, l, m, pii(x, id));
        split(m, m, r, pii(x, id+1));
        root = mrg(l, r);
        if (m) {
            delete m;
        }
    }

    void ins (int x, int id) {
        Node *nw = new Node(x, id);
        if (!root) {
            root = nw;
        } else {
            Node *l, *r;
            split(root, l, r, pii(x, id));
            root = mrg(l, mrg(nw, r));
        }
    }

    int qry (int l, int r) {
        Node *L, *M, *R;
        split(root, L, M, pii(l, -iNF));
        split(M, M, R, pii(r+1, -iNF));
        int ret = SIZ(M);
        root = mrg(L, mrg(M, R));
        return ret;
    }
} trp[MAXN];
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    cin >> n >> k;
    REP (i, n) {
        cin >> rbt[i].x >> rbt[i].r >> rbt[i].q;
        qval.eb(rbt[i].q);
    }
    sort(ALL(qval));
    qval.resize(unique(ALL(qval)) - qval.begin());
    REP (i, n) {
        rbt[i].qid = lower_bound(ALL(qval),rbt[i].q) - qval.begin();
    }

    sort(rbt, rbt + n, [&](Robot r1, Robot r2) {
        return r1.x < r2.x;
    });

    priority_queue<pii, vector<pii>, greater<pii> > pq;
    REP (i, n) {
        debug(i);
        int x = rbt[i].x, r = rbt[i].r, q = rbt[i].q, qid = rbt[i].qid;
        while (!pq.empty() && pq.top().X < x) {
            int id = pq.top().Y;
            trp[rbt[id].qid].era(rbt[id].x, id);
            pq.pop();
        }

        int ptr = qid;
        while (ptr > 0 && q-qval[ptr-1] <= k) {
            ptr--;
        }
        while (ptr < SZ(qval) && abs(q-qval[ptr]) <= k) {
            ans += trp[ptr].qry(x-r, x+r);
            ptr++;
        }

        pq.emplace(x+r, i);
        trp[qid].ins(x, i);

    }

    cout << ans << endl;
    return 0;
}
