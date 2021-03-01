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

int n, m, a[MAXN], on[MAXN * 4], flip[MAXN * 4], len[MAXN * 4];

int get (int o) {
    return flip[o] ? len[o] - on[o] : on[o];
}

void build (int o, int l, int r) {
    if (l + 1 == r) {
        len[o] = r - l;
    } else {
        int mid = (l + r) >> 1;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        len[o] = len[o<<1] + len[o<<1|1];
    }
}

void push (int o) {
    if (flip[o]) {
        on[o] = len[o] - on[o];
        flip[o<<1] ^= 1;
        flip[o<<1|1] ^= 1;
        flip[o] = 0;
    }
}

void pull (int o) {
    on[o] = get(o<<1) + get(o<<1|1);
}

void upd (int o, int nL, int nR, int qL, int qR) {
    if (nL < qR && nR > qL && qL < qR) {
        if (nL >= qL && nR <= qR) {
            flip[o] ^= 1;
        } else {
            int mid = (nL + nR) >> 1;
            push(o);
            upd(o<<1, nL, mid, qL, qR);
            upd(o<<1|1, mid, nR, qL, qR);
            pull(o);
        }
    }
}

int qry (int o, int nL, int nR, int qL, int qR) {
    if (nL < qR && nR > qL && qL < qR) {
        if (nL >= qL && nR <= qR) {
            return get(o);
        } else {
            int mid = (nL + nR) >> 1;
            push(o);
            return qry(o<<1, nL, mid, qL, qR) + qry(o<<1|1, mid, nR, qL, qR);
        }
    } else {
        return 0;
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    build(1, 0, n);
    while (m--) {
        int cmd, l, r;
        cin >> cmd >> l >> r;
        if (cmd == 0) {
            upd(1, 0, n, l-1, r);
        } else {
            cout << qry(1, 0, n, l-1, r) << endl;
        }
    }
    return 0;
}
