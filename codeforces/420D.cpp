#include <bits/stdc++.h>
using namespace std;
typedef int ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
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
// const ll MAXN = 

struct Node {
    Node *l,*r;
    ll data,pri,sz;
    void pull() {
        sz = true;
        if (l) {
            sz += l->sz;
        }
        if (r) {
            sz += r->sz;
        }
    }

    Node () {
        data = -1;
        pri = rand();
        sz = 1;
        l = r = 0;
    }
};
ll SIZ(Node *a) {
    return a ? a->sz : 0;
}

Node *merge(Node *a,Node *b) {
    if (!a || !b) {
        return a ? a : b;
    }
    if (a->pri > b->pri) {
        a->r = merge(a->r,b);
        a->pull();
        return a;
    } else {
        b->l = merge(a,b->l);
        b->pull();
        return b;
    }
}

void split_by_size(Node *o,Node *&a,Node *&b,ll k) {
    if (!o) {
        a = b = 0;
        return;
    }
    if (SIZ(o->l) + 1 <= k) {
        a = o;
        split_by_size(o->r,a->r,b,k-SIZ(o->l)-1);
        a->pull();
    } else {
        b = o;
        split_by_size(o->l,a,b->l,k);
        b->pull();
    }
}

ll n,m;
Node *root;

vector<pii> query;
ll ptr = 1;
bitset<1000002> vis;

vector<ll> ans;
void traversal(Node *nd) {
    if (nd->l) {
        traversal(nd->l);
    }
    while (vis[ptr]) {
        ptr++;
    }
    if (nd->data != -1) {
        ans.eb(nd->data);
    } else {
        ans.eb(ptr);
        vis[ptr] = true;
    }
    if (nd->r) {
        traversal(nd->r);
    }
    
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    srand(time(0));
    cin >> n >> m;
    REP (i,n) {
        Node *tmp = new Node();
        if (root) {
            root = merge(root,tmp);
        } else {
            root = tmp;
        }
        debug(SIZ(root),SIZ(tmp));
    }

    REP (i,m) {
        ll x,y;
        cin >> x >> y;
        query.eb(x,y);
    }

    reverse(ALL(query));

    REP (i,m) {
        Node *l,*r;
        split_by_size(root,l,r,1);
        if (l->data != -1 && l->data != query[i].X) {
            cout << -1 << endl;
            return 0;
        } else if (l->data == -1) {
            if (vis[query[i].X]) {
                cout << -1 << endl;
                return 0;
            } 
            l->data = query[i].X;
            vis[l->data] = true;
        }
        Node *rl,*rr;
        split_by_size(r,rl,rr,query[i].Y-1);
        debug(SIZ(rl),SIZ(rr),SIZ(l));
        root = merge(merge(rl,l),rr);
    }

    traversal(root);

    for (auto v : ans) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
