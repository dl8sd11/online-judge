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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif


const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;

template<class T>
struct SegmentTree {
    struct Data {
        T _dt[3];
        T &operator[] (const int idx) {
            return _dt[idx];
        }
        Data(T e1,T e2,T e3){
             _dt[0] = e1;
             _dt[1] = e2;
             _dt[2] = e3;
        }
        Data(){}
    };
    struct node {
        int l,r;
        node *lc,*rc;
        Data data; // mn, mx, sum;
        T mn,mx,sm;
        T chg,add;
        bool is_chg;
        Data get () {
            Data ret;
            ret[0] = (is_chg ? chg: data[0]) + add; 
            ret[1] = (is_chg ? chg: data[1]) + add; 
            ret[2] = (is_chg ? chg * (r-l): data[2]) + add * (r-l); 
            return ret;
        }

        void push() {
            if (is_chg) {
                data[0] = chg;
                data[1] = chg;
                data[2] = chg*(r-l);
                if (lc && rc) {
                    lc->is_chg = true;
                    lc->chg = chg;
                    lc->add = 0;
                    rc->is_chg = true;
                    rc->chg = chg;
                    rc->add = 0;
                }
                is_chg = false;
            }
            if (add != 0) {
                data[0] += add;
                data[1] += add;
                data[2] += add * (r-l);
                if (lc && rc) {
                    lc->add += add;
                    rc->add += add;
                }
                add = 0;
            }
        }

        void pull () {
            if (lc && rc) {
                data[0] = min(lc->get()[0],rc->get()[0]);
                data[1] = max(lc->get()[1],rc->get()[1]);
                data[2] = lc->get()[2] + rc->get()[2];
            }
        }

        node (int li,int ri,node *lci,node *rci,T dt) : l(li),r(ri),lc(lci),rc(rci) {
            data[0] = data[1] = data[2] = dt;
            add = 0;
            is_chg = false;
        }
    };
    T seg[MAXN];
    node *root;

    node *build(int l,int r) {
        if (r == l+1) {
            return new node(l,r,0,0,seg[l]);
        }
        int mid = (l+r) >> 1;
        node *ret = new node(l,r,build(l,mid),build(mid,r),0);
        ret->pull();
        return ret;
    }

    void init(int sz) {
        root = build(0,sz);
    }

    Data query(int l,int r,node *nd) {
        if (l == nd->l && r == nd->r) {
            return nd->get();
        }
        nd->push();
        int mid = (nd->l + nd->r) >> 1;
        if (l >= mid) {
            return query(l,r,nd->rc);
        } else if (r <= mid) {
            return query(l,r,nd->lc);
        } else {
            Data lret = query(l,mid,nd->lc),rret = query(mid,r,nd->rc);
            return Data(min(lret[0],rret[0]),max(lret[1],rret[1]),lret[2]+rret[2]);
        }

    }

    void add(int l,int r,T val,node *nd) {
        if (l == nd->l && r == nd->r) {
            nd->add += val;
            return;
        }
        nd->push();
        int mid = (nd->l + nd->r) >> 1;
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

    void change(int l,int r,T val,node *nd) {
        if (l == nd->l && r == nd->r) {
            nd->add = 0;
            nd->is_chg = true;
            nd->chg = val;
            return;
        }
        nd->push();
        int mid = (nd->l + nd->r) >> 1;
        if (l >= mid) {
            change(l,r,val,nd->rc);
        } else if (r <= mid) {
            change(l,r,val,nd->lc);
        } else {
            change(l,mid,val,nd->lc);
            change(mid,r,val,nd->rc);
        }
        nd->pull();
    }
};

int n,m;
SegmentTree<ll> ds;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,n) {
        cin >> ds.seg[i];
    }
    ds.init(n);

    while (m--) {
        string cmd;
        cin >> cmd;
        if (cmd == "add") {
            int l,r;
            ll val;
            cin >> l >> r >> val;
            ds.add(l-1,r,val,ds.root);
        } else if (cmd == "set") {
            int l,r;
            ll val;
            cin >> l >> r >> val;
            ds.change(l-1,r,val,ds.root);
        } else if (cmd == "sum") {
            int l,r;
            cin >> l >> r;
            cout << ds.query(l-1,r,ds.root)[2] << endl;
        } else if (cmd == "max") {
            int l,r;
            cin >> l >> r;
            cout << ds.query(l-1,r,ds.root)[1] << endl;
        } else if (cmd == "min") {
            int l,r;
            cin >> l >> r;
            cout << ds.query(l-1,r,ds.root)[0] << endl;
        } else {
            assert("Input Error" == 0);
        }
    }
    return 0;
}
