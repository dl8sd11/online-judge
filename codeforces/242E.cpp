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
const ll MAXD = 20;
int n, m, a[MAXN], cnt[MAXN*4][MAXD], len[MAXN*4];
bool flip[MAXN*4][MAXD];

int getCnt (int o, int d) {
    return flip[o][d] ? len[o] - cnt[o][d] : cnt[o][d];
}

void push (int o) {
    REP (i, MAXD) {
        if (flip[o][i]) {
            cnt[o][i] = len[o] - cnt[o][i];
            flip[o][i] = false;
            flip[o<<1][i] ^= 1;
            flip[o<<1|1][i] ^= 1;
        }
    }
}


void pull (int o) {
    REP (i, MAXD) {
        cnt[o][i] = getCnt(o<<1, i) + getCnt(o<<1|1, i);
    }
}

void build (int o, int l, int r) {
    if (l == r - 1) {
        REP (i, MAXD) {
            cnt[o][i] = (a[l] >> i) & 1;
            len[o] = 1;
        }
    } else {
        int mid = (l + r) >> 1;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        len[o] = len[o<<1] + len[o<<1|1];
        pull(o);
    }
}

ll sum (int o) {
    ll ret = 0;
    REP (i, MAXD) {
        ret += getCnt(o, i) * (1LL<<i);
    }
    return ret;
}

ll query(int o, int nL, int nR, int qL, int qR) {
    if (qR <= nL || qL >= nR || qL >= qR) {
        return 0;
    } else if (nL >= qL && nR <= qR) {
        return sum(o);
    } else {
        push(o);
        int mid = (nL + nR) >> 1;
        return query(o<<1, nL, mid, qL, qR) + query(o<<1|1, mid, nR, qL, qR);
    }
}

void modify(int o, int nL, int nR, int qL, int qR, int val) {
    if (qR <= nL || qL >= nR || qL >= qR) {
        return;
    } else if (nL >= qL && nR <= qR) {
        REP (i, MAXD) {
            flip[o][i] ^= (val>>i) & 1;
        }
    } else {
        push(o);
        int mid = (nL + nR) >> 1;
        modify(o<<1, nL, mid, qL, qR, val);
        modify(o<<1|1, mid, nR, qL, qR, val);
        pull(o);
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

    cin >> m;
    while (m--) {
        int t, l, r, val;
        cin >> t >> l >> r;
        if (t == 1) {
            cout << query(1, 0, n, l-1, r) << endl;
        } else {
            cin >> val;
            modify(1, 0, n, l-1, r, val);
        }
    }
    return 0;
}
