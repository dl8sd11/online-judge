#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 100005;

ll n, q, dt[MAXN];

struct Data {
    ll mx, mn, ans;
};

struct Node {
    int l, r;
    Node *lc, *rc;
    Data d;
    void pull() {
        if (lc && rc) {
            d.ans = max({lc->d.ans,rc->d.ans,(lc->d.mx-rc->d.mn)});
            d.mx = max(lc->d.mx, rc->d.mx);
            d.mn = min(lc->d.mn, rc->d.mn);
        }
    }
};

Node *build(int l, int r) {
    if (r == l + 1) {
        return new Node{l, r, 0, 0, {dt[l],dt[l],-INF}};
    } else {
        int mid = (l + r) >> 1;
        Node *ret = new Node{l, r, build(l, mid), build(mid, r),{-INF,INF,-INF}};
        ret->pull();
        return ret;
    }
}

void upd(int pos, ll val, Node *nd) {
    if (nd->r == nd->l + 1) {
        nd->d.mx = nd->d.mn = val;
    } else {
        int mid = (nd->l + nd->r) >> 1;
        if (pos >= mid) {
            upd(pos, val, nd->rc);
        } else {
            upd(pos, val, nd->lc);
        }
        nd->pull();
    }
}

Data qry(int l, int r, Node *nd) {
    if (l == nd->l && r == nd->r) {
        return nd->d;
    } else {
        int mid = (nd->l + nd->r) >> 1;
        if (l >= mid) {
            return qry(l, r, nd->rc);
        } else if (r <= mid) {
            return qry(l, r, nd->lc);
        } else {
            Data lD = qry(l, mid, nd->lc);
            Data rD = qry(mid, r, nd->rc);
            Data ret;
            ret.ans = max({lD.ans,rD.ans,(lD.mx-rD.mn)});
            ret.mx = max(lD.mx, rD.mx);
            ret.mn = min(lD.mn, rD.mn);
            return ret;
        }
    }
}

// void dfs(Node *nd) {
//     debug(nd->d.ans,nd->d.ans,nd->d.ans)
// }
Node *root;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> q;
    REP (i, n) {
        cin >> dt[i];
    }
    root = build(0, n);
    debug(root->d.ans);
    debug(root->d.mx);
    debug(root->d.mn);
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            upd(b-1, c, root);
        } else {
            cout << qry(b-1,c,root).ans << endl;
        }
    }
    return 0;
}
