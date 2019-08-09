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
const ll MAXN = 30004;

int n, q, a[MAXN];
vector<int> val;

struct Node {
    int l, r;
    Node *lc, *rc;
    int sz;

    void pull() {
        if (lc && rc) {
            sz = lc->sz + rc->sz;
        }
    }
};
Node *root[MAXN];

Node *build(int l, int r) {
    if (l == r - 1) {
        return new Node{l, r, nullptr, nullptr, 0};
    } else {
        int mid = (l + r) >> 1;
        return new Node{l, r, build(l, mid), build(mid, r), 0};
    }
}

Node *add(int pos, Node *nd) {
    if (pos == nd->l && pos + 1 == nd->r) {
        Node *ret = new Node(*nd);
        ret->sz++;
        return ret;
    } else {
        Node *ret = new Node(*nd);
        int mid = (nd->l + nd->r) >> 1;
        if (pos < mid) {
            ret->lc = add(pos, nd->lc);
        } else {
            ret->rc = add(pos, nd->rc);
        }
        ret->pull();
        return ret;
    }
}

int query(int l, int r, Node *nd) {
    if (l == r) {
        return 0;
    }
    debug(l, r, nd->l, nd->r);
    if (l == nd->l && r == nd->r) {
        return nd->sz;
    } else {
        int mid = (nd->l + nd->r) >> 1;
        if (l >= mid) {
            return query(l, r, nd->rc);
        } else if (r <= mid) {
            return query(l, r, nd->lc);
        } else {
            return query(l, mid, nd->lc) + query(mid, r, nd->rc);
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;

    REP1 (i, n) {
        cin >> a[i];
        val.eb(a[i]);
    }
    sort(ALL(val));
    val.resize(unique(ALL(val))-val.begin());

    root[0] = build(0, SZ(val));
    REP1 (i, n) {
        root[i] = add(lower_bound(ALL(val), a[i])-val.begin(), root[i-1]);
    }
    pary(root, root+n+1);

    cin >> q;
    int lst = 0;
    while (q--) {
        int A, B, C;
        cin >> A >> B >> C;
        A ^= lst, B ^= lst, C ^= lst;
        debug(A, B, C);
        if (A < 1) {
            A = 1;
        }
        if (B > n) {
            B = n;
        }
        if (A > B) {
            lst = 0;
            cout << lst << endl;
        } else {
            int l = upper_bound(ALL(val), C) - val.begin();
            lst = query(l, SZ(val), root[B]) - query(l, SZ(val), root[A-1]);
            cout << lst << endl;
        }
    }
    return 0;
}
