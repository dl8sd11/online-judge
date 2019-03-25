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
const ll MAXN = 100002;


ll a[MAXN],k[MAXN],n,q;
set<ll> sr;

struct Node {
    ll l,r;
    Node *lc,*rc;
    ll data,tag;

    ll get() {
        return data + tag*(r-l);
    }

    void push() {
        data += tag*(r-l);
        if (lc && rc) {
            lc->tag += tag;
            rc->tag += tag;
        }
        tag = 0;
    }
    void pull() {
        if (lc && rc) {
            data = lc->get() + rc->get();
        }
    }
};

Node *build(ll l,ll r) {
    if (r == l + 1) {
        return new Node{l,r,0,0,a[l],0};
    }
    ll mid = (l + r) >> 1;
    Node *ret = new Node{l,r,build(l,mid),build(mid,r),0,0};
    ret->pull();
    return ret;
}

Node *root;
void add(ll l,ll r,ll val,Node *nd = root) {
    if (l == nd->l && r == nd->r) {
        nd->tag += val;
        return;
    }
    nd->push();
    ll mid = (nd->l + nd->r) >> 1;
    if (l >= mid) {
        add(l,r,val,nd->rc);
    } else if (r <= mid) {
        add(l,r,val,nd->lc);
    } else {
        add(l,mid,val,nd->lc);
        add(mid,r,val,nd->rc);
    }
    nd->pull();
}

ll query(ll l,ll r,Node *nd = root) {
    if (l == nd->l && r == nd->r) {
        return nd->get();
    }
    nd->push();
    ll mid = (nd->l + nd->r) >> 1;
    if (l >= mid) {
        return query(l,r,nd->rc);
    } else if (r <= mid) {
        return query(l,r,nd->lc);
    } else {
        return query(l,mid,nd->lc) + query(mid,r,nd->rc);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> a[i];
        sr.insert(i);
    }
    REP (i,n-1) {
        cin >> k[i];
    }
    root = build(0,n);
    cin >> q;
    while (q--) {
        char cmd;
        cin >> cmd;
        if (cmd == '+') {
            ll i,x;
            cin >> i >> x;
            i--;
            if (x) {
                sr.insert(i-1);
                ll ptr = *sr.lower_bound(i);
                while(ptr != -1) {
                    debug(ptr,x);
                    add(i,ptr+1,x);
                    i = ptr+1;
                    if (ptr+1 < n && query(ptr,ptr+1)+k[ptr] > query(ptr+1,ptr+2)) {
                        sr.erase(ptr);
                        auto tmp = sr.lower_bound(ptr+1);
                        if (tmp == sr.end()) {
                            ptr = -1;
                        } else {
                            x = query(ptr,ptr+1)+k[ptr]- query(ptr+1,ptr+2);
                            ptr = *tmp;
                        }
                    } else {
                        break;
                    }
                }
            }
        } else {
            ll L,R;
            cin >> L >> R;
            cout << query(L-1,R) << endl;
        }

        #ifdef tmd
        REP (i,n) {
            cout << query(i,i+1) << " \n"[i==n-1];
        }
        #endif
    }

    return 0;
}
