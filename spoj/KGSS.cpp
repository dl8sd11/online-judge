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

int n, q, a[MAXN];
pair<int,int> t[MAXN*4];

pair<int,int> pull(pair<int,int> &p1, pair<int,int> &p2) {
    array<int, 4> ar = {p1.X, p1.Y, p2.X, p2.Y};
    sort(ALL(ar));
    return {ar[3], ar[2]};
}

void build(int o, int l, int r) {
    if (l  == r - 1) {
        t[o].X = a[l];
        t[o].Y = -iNF;
    } else {
        int mid = (l + r) >> 1;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        t[o] = pull(t[o<<1], t[o<<1|1]);
    }
}

void upd(int o, int nL, int nR, int pos, int val) {
    if (nL == pos && nR - 1 == pos) {
        t[o].X = val;
        t[o].Y = -iNF;
    } else {
        int mid = (nL + nR) >> 1;
        if (pos >= mid) {
            upd(o<<1|1, mid, nR, pos, val);
        } else {
            upd(o<<1, nL, mid, pos, val);
        }
        t[o] = pull(t[o<<1], t[o<<1|1]);
    }
}

pair<int, int> query(int o, int nL, int nR, int qL, int qR) {
    if (qR <= nL || qL >= nR || qL >= qR) {
        return {-iNF, -iNF};
    } else if (nL >= qL && nR <= qR) {
        return t[o];
    } else {
        int mid = (nL + nR) >> 1;
        pair<int,int> rL = query(o<<1, nL, mid, qL, qR), rR = query(o<<1|1, mid, nR, qL, qR);
        return pull(rL, rR);
    }
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i, n) {
        cin >> a[i];
    }
    build(1, 0, n);

    cin >> q;
    while (q--) {
        char cmd;
        cin >> cmd;
        if (cmd == 'U') {
            int pos, val;
            cin >> pos >> val;
            upd(1, 0, n, pos-1, val);
        } else {
            int l, r, m1, m2;
            cin >> l >> r;
            tie(m1, m2) = query(1, 0, n, l-1, r);
            cout << m1 + m2 << endl;
        }
    }
    return 0;
}
