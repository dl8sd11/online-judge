#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3", "unroll-loops")
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
const ll MAXN = 500005;
const int MAXLG = __lg(MAXN) + 3;

struct node {
    node *lc,*rc;
    int l,r;
    ll data;

    void pull () {
        data = 0;
        if (lc) {
            data += lc->data;
        }
        if (rc) {
            data += rc->data;
        }
    }
};
node *root[MAXN], *minu[MAXN];
node nodes[MAXN*MAXLG*5]; // pool to avoid new
int n, q, ncnt;


node* newNode (int l, int r) {
    node *ret = &nodes[ncnt];
    ret->lc = ret->rc = 0;
    ret->l = l;
    ret->r = r;
    ret->data = 0;
    ncnt++;
    return ret;
}

void init () {
    for (int i=1;i<=n;i++) {
        root[i] = newNode(0,n);
        minu[i] = newNode(0,n);
    }
}

ll query(int l, node *nd) {
    if (!nd || nd->r <= l) {
        return 0;
    } else if (l <= nd->l) {
        return nd->data;
    } else {
        return query(l,nd->lc) + query(l,nd->rc);
    }
}

void ins(int pos,ll val,node *nd) {
    if (nd->l == pos && nd->r == pos+1) {
        nd->data += val;
    } else {
        int mid = (nd->l + nd->r) >> 1;
        if(pos >= mid) {
            if (!nd->rc) {
                nd->rc = newNode(mid,nd->r);
            }
            ins(pos,val,nd->rc);
        } else {
            if (!nd->lc) {
                nd->lc = newNode(nd->l,mid);
            }
            ins(pos,val,nd->lc);
        }
        nd->pull();
    }
}


vector<int> edge[MAXN];
bool dead[MAXN];
int sz[MAXN], anc[MAXN][MAXLG], dep[MAXN], pG[MAXN];

int OneCentroid(int rt) {
    function<void (int,int)> get_sz = [&](int nd,int par) {
        sz[nd] = 1;
        for (auto v : edge[nd]) {
            if (v != par && !dead[v]) {
                get_sz(v,nd);
                sz[nd] += sz[v];
            }
        }
    };
    get_sz(rt,-1);
    int hf = sz[rt] / 2;
    function<int (int,int)> dfs = [&](int nd,int par) {
        for (auto v : edge[nd]) {
            if (v != par && !dead[v] && sz[v] > hf) {
                return dfs(v,nd);
            }
        }
        return nd;
    };
    return dfs(rt,rt);
}

void CentroidDecomposition() {

    function<void (int,int,int,int)> get_child = [&](int nd,int par,int d,int lev) {
        anc[nd][lev] = d;
        for (auto v : edge[nd]) {
            if (v != par && !dead[v]) {
                get_child(v,nd,d+1,lev);
            }
        }
    };
    function<void (int,int,int)> rec = [&](int start,int par,int lev) {
        int c = OneCentroid(start);
        dead[c] = true;
        pG[c] = par;
        dep[c] = lev;

        get_child(c,-1,0,lev);

        for (auto v : edge[c]) {
            if (!dead[v]) {
                rec(v,c,lev+1);
            }
        }

        dead[c] = false;
    };
    rec(1,-1,0);
}

void add(int start, int d, ll val) {
    function<void (int)> pull = [&](int nd) {
        int dis = d - anc[start][dep[nd]];
        if (dis >= 0) {
            ins(dis, val, root[nd]);
        }
        if (pG[nd] != -1) {
            int d2 = d - anc[start][dep[nd]-1];
            if (d2 >= 0) {
                ins(d2, val, minu[nd]);
            }
            pull(pG[nd]);
        }
    };
    pull(start);
}

ll qry(int start) {
    ll ret = 0;
    function<void (int,int)> pull = [&](int nd,int lst) {
        ret += query(anc[start][dep[nd]], root[nd]);

        if (pG[nd] != -1) {
            ret -= query(anc[start][dep[nd]-1], minu[nd]);
            pull(pG[nd],nd);
        }
    };
    pull(start,-1);
    return ret;
}

ll L;
signed main () {
    TIME(main);
    IOS();

    cin >> n;
    init();

    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }
    CentroidDecomposition();

    cin >> q;
    // remember to hash the input
    while (q--) {
        int cmd, x, d, v;
        cin >> cmd >> x;

        x = (x + L - 1) % n;
        if (x < 0) {
            x += n;
        }
        x++;

        if (cmd == 1) {
            cin >> d >> v;
            d = (d + L) % n;
            if (d < 0) {
                d += n;
            }
            add(x, d, v);
        } else {
            L = qry(x);
            cout << L << endl;
        }
    }


    return 0;
}
/*
10
2 1
3 2
4 2
5 4
6 1
7 2
8 5
9 4
10 8
2
1 9 5 9
2 9
*/