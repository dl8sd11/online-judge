#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
const ll MAXN = 1000003; 

ll n,a[MAXN];
map<ll,ll> pre,suf;

namespace TRP {
    const ll ra = 880301,rb = 53, rm = 20020607;
    ll rn = 97;
    int random () {
        return rn = (rn*ra+rb) % rm;
    }


    struct Node {
        Node *l,*r;
        ll key,val,tag;
        int sz,pri;
        Node (ll k,ll v) {
            l = r = 0;
            pri = random();
            key = k;
            tag = val = v;
            sz = 1;
        }

        void pull() {
            sz = 1;
            tag = val;
            if (l) {
                tag = max(tag,l->tag);
                sz += l->sz;
            }
            if (r) {
                tag = max(tag,r->tag);
                sz += r->sz;
            }
        }
    };
    Node *root;

    int SIZ(Node *nd) {
        return nd ? nd->sz : 0;
    }

    Node *mrg(Node *a,Node *b) {
        if (!a || !b) {
            return a ? a : b;
        }
        if (a->pri > b->pri) {
            a->r = mrg(a->r,b);
            a->pull();
            return a;
        } else {
            b->l = mrg(a,b->l);
            b->pull();
            return b; 
        }
    }

    // max a key <= key
    void split_key(Node *o,Node *&a,Node *&b,ll key) {
        if (!o) {
            a = b = 0;
            return;
        }
        if (o->key <= key) {
            a = o;
            split_key(o->r,a->r,b,key);
            a->pull();
        } else {
            b = o;
            split_key(o->l,a,b->l,key);
            b->pull();
        }
    }

    // size of a equals sz
    void split_sz(Node *o,Node *&a,Node *&b,ll sz) {
        if (!o) {
            a = b = 0;
            return;
        }
        if (SIZ(o->l)+1 <= sz) {
            a = o;
            split_sz(o->r,a->r,b,sz-SIZ(o->l)-1);
            a->pull();
        } else {
            b = o;
            split_sz(o->l,a,b->l,sz);
            b->pull();
        }
    }

    void ins(ll key,ll val) {
        Node *nw = new Node(key,val);
        if (!root) {
            root = nw;
        } else {
            Node *l,*r;
            split_key(root,l,r,key);
            root = mrg(l,mrg(nw,r));
        }
    }

    // static rmq on treap lol
    ll query(ll val) {
        Node *a,*b;
        split_key(root,a,b,val-1);
        ll ret = SIZ(a);
        root = mrg(a,b);
        return ret;
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> a[i];
        pre[a[i]]++;
    }

    ll ans = 0;
    for (ll i=n-1;i>0;i--) {
        TRP::ins(++suf[a[i]],0);
        pre[a[i]]--;
        ans += TRP::query(pre[a[i-1]]);
    }

    cout << ans << endl;
    return 0;
}
