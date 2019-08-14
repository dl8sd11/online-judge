#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const int MAXN = 5003;

int n, bit[MAXN*2];
vector<pair<int,pii> > h, v;

void add(int x) {
    for (;x < MAXN*2; x+=-x&x) {
        bit[x]++;
    }
}

int qry(int x) {
    int ret = 0;
    for (; x > 0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int qry(int l, int r) {
    if (l > r) {
        return 0;
    }
    return qry(r) - qry(l-1);
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i, n) {
        int xf, xs, yf, ys;
        cin >> xf >> yf >> xs >> ys;
        xf += MAXN, xs += MAXN;
        if (xf == xs) {
            if (yf > ys) {
                swap(yf, ys);
            }
            v.eb(xf, pii(yf, ys));
        } else {
            if (xf > xs) {
                swap(xf, xs);
            }
            h.eb(yf, pii(xf, xs));
        }
    }
    sort(ALL(h), [&](pair<int,pii> p1, pair<int,pii> p2) {
        return p1.X < p2.X;
    });

    sort(ALL(v), [&](pair<int,pii> p1, pair<int,pii> p2) {
        return p1.Y.Y > p2.Y.Y;
    });
    debug(v);
    debug(h);

    ll ans = 0;
    REP (i, SZ(h)) {
        int ptr = 0;
        MEM(bit, 0);
        for (int j=SZ(h)-1; j > i; j--) {
            while (ptr < SZ(v) && v[ptr].Y.Y >= h[j].X) {
                if (v[ptr].Y.X <= h[i].X) {
                    add(v[ptr].X);
                }
                ptr++;
            }
            debug(i, j, max(h[i].Y.X, h[j].Y.X), min(h[i].Y.Y, h[j].Y.Y));
            int cnt = qry(max(h[i].Y.X, h[j].Y.X), min(h[i].Y.Y, h[j].Y.Y));
            ans += ll(cnt) * (cnt - 1) / 2;
            debug(cnt);
        }
    }
 
    cout << ans << endl;
    return 0;
}
