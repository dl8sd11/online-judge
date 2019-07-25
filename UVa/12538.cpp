#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 50004;


int n, cmd, p, c, v, d, cur;
struct Node {
    Node *l, *r;
    int pri, sz;
    char c;
    Node (char cc) {
        l = r = nullptr;
        pri = rand();
        sz = 1;
        c = cc;
    }

    void pull() {
        sz = 1;
        if (l) {
            sz += l->sz;
        }
        if (r) {
            sz += r->sz;
        }
    }
};
Node *root[MAXN];

void copy(Node *&a, Node *b) {
    if (b) {
        a = new Node(*b);
    } else {
        a = nullptr;
    }
}

Node *merge(Node *a, Node *b) {
    Node *ret;
    if (!a) {
        copy(ret, b);
    } else if (!b) {
        copy(ret, a);
    } else if (a->pri < b->pri) {
        copy(ret, a);
        ret->r = merge(ret->r, b);
        ret->pull();
    } else {
        copy(ret, b);
        ret->l = merge(a, ret->l);
        ret->pull();
    }
    return ret;
}

int SIZ(Node *o) {
    return o ? o->sz : 0;
}

void split(Node *o, Node *&a, Node *&b, int k) {
    if (!o) {
        a = b = nullptr;
    } else if (SIZ(o->l) >= k) {
        copy(b, o);
        split(b->l, a, b->l, k);
        b->pull();
    } else {
        copy(a, o);
        split(a->r, a->r, b, k-SIZ(a->l)-1);
        a->pull();
    }
}

Node *insert(Node *nd, int p, string str) {

}

Node *remove(Node *nd, int p, int c) {

}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    while (n--) {
        cin >> cmd;
        if (cmd == 1) {
            string str;
            cin >> p >> str;
            p -= d;
            insert(p, str);
        } else if (cmd == 2) {
            cin >> p >> c;
            p -= d;
            c -= d;
            remove(p, c);
        } else {
            cin >> v >> p >> c;
            v -= d;
            p -= d;
            c -= d;
            output(v, p, c);
        }
    }
    return 0;
}
