#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<double,double> pdd;
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
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const int INF = 0x3f3f3f3f;
const int MAXN = 200003;
const int MAXC = (1<<20) + 3;

int t,n,q,w[MAXN],in[MAXN],out[MAXN],ts;
vector<int> edge[MAXN];
/***persistence*segment*tree***/
namespace SEG {
    struct node {
        int l,r;
        node *lc,*rc;
        int sum;
        void pull() {
            if (lc && rc) {
                sum = lc->sum + rc->sum;
            }
        }
    };
    node *root[MAXN];

    node *build(int l,int r) {
        if (r == l + 1) {
            return new node{l,r,0,0,0};
        } else {
            int mid = (l + r) >> 1;
            return new node{l,r,build(l,mid),build(mid,r),0};
        }
    }

    node *add(int pos,node *nd) {
        node *ret = new node(*nd);
        if (nd->l == pos && nd->r == pos+1) {
            ret->sum += 1;
        } else {
            int mid = (nd->l + nd->r) >> 1;
            if (pos >= mid) {
                ret->rc = add(pos,ret->rc);
            } else {
                ret->lc = add(pos,ret->lc);
            }
            ret->pull();
        }
        return ret;
    }

    int binary_search(int k,int d,node *l,node *r) {
        if (d == -1) {
            // while(l->l != l->r - 1); True   
            return l->l;
        } else {
            int lsum = r->lc->sum - l->lc->sum;
            int rsum = r->rc->sum - l->rc->sum;
            if (lsum == 0) {
                return binary_search(k,d-1,l->rc,r->rc);
            } else if (rsum == 0) {
                return binary_search(k,d-1,l->lc,r->lc);
            } else {
                if ((k>>d) & 1) {
                    return binary_search(k,d-1,l->lc,r->lc);
                } else {
                    return binary_search(k,d-1,l->rc,r->rc);
                }
            }
        }
    }
};
namespace LG {
    vector<pii> seg[MAXN*2];

    void rst() {
        for (int i=0;i<=n*2;i++) {
            seg[i].clear();
            seg[i].shrink_to_fit();
        }
    }

    void srt() {
        for (int i=0;i<=n*2;i++) {
            sort(ALL(seg[i]));
        }
    }

    void add(int pos,int nd) {
        for (pos+=n;pos>=1;pos>>=1) {
            seg[pos].eb(w[nd],nd);
        }
    }

    int query(int l,int r,int v) {
        int ret = INF;
        for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
            if (l&1) {
                auto it = upper_bound(ALL(seg[l]),pii(v,INF));
                if (it != seg[l].begin() && seg[l].size()) {
                    it = prev(it);
                    if (it->X == v) {
                        ret = min(ret,it->Y);
                    }
                }
                l++;
            }
            if (r&1) {
                r--;
                auto it = upper_bound(ALL(seg[r]),pii(v,INF));
                if (it != seg[r].begin() && seg[r].size()) {
                    it = prev(it);
                    if (it->X == v) {
                        ret = min(ret,it->Y);
                    }
                }
            }
        }
        // while(ret == INF);
        return ret;
    }
};
/***********Solution***********/

pii query(int v,int k) {
    // while (v <= 0 || v > n); False
    int mx = SEG::binary_search(k,19,SEG::root[in[v]],SEG::root[out[v]]);//w[v];//
    int id = LG::query(in[v],out[v],mx);
    return {id,mx^k};
}

void dfs(int nd,int par) {
    LG::add(ts,nd);
    // (in,out] is the range of the subtree of nd
    SEG::root[ts+1] = SEG::add(w[nd],SEG::root[ts]);
    in[nd] = ts++;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v,nd);
        }
    }
    out[nd] = ts;
}

inline char readchar()
{
    static const size_t bufsize = 65536;
    static char buf[bufsize];
    static char *p = buf, *end = buf;
    if (p == end) end = buf + fread_unlocked(buf, 1, bufsize, stdin), p = buf;
    return *p++;
}

template <class T> void input(T& a)
{
    static char p;
    while ((p = readchar()) < '0') ;
    a = p ^ '0';
    while ((p = readchar()) >= '0') a *= 10, a += p ^ '0';
}

/********** Good Luck :) **********/
int main()
{
    // IOS();
    // cin >> t;
    // input(t);
    scanf(" %d",&t);
    SEG::root[0] = SEG::build(0,1<<20);

    while (t--) {
        // cin >> n >> q;
        scanf(" %d %d",&n,&q);
        // input(n);input(q);
        REP1 (i,n) {
            // input(w[i]);
            // cin >> w[i];
            scanf(" %d",&w[i]);
        }
        debug(n,q);
        REP (i,n-1) {
            int u,v;
            scanf(" %d %d",&u,&v);
            // input(u);input(v);
            // cin >> u >> v;
            edge[u].eb(v);
            edge[v].eb(u);
        }
        // build tree
        ts = 0;
        dfs(1,1);
        LG::srt();

        // process queries
        int x = 0,v = 0;
        while (q--) {
            int a,b;
            // cin >> a >> b;
            // input(a);input(b);
            scanf(" %d %d",&a,&b);
            tie(v,x) = query(a^v,b^x);//query(rand()%n+1,123);
            printf("%d %d\n",v,x);
            // cout << v << " " << x << endl;
        }

        // reset graph
        REP1 (i,n) {
            edge[i].clear();
            edge[i].shrink_to_fit();
        }
        LG::rst();
    }
    return 0;
}
