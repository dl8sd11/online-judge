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
const ll MAXN = 200005;

ll n, ans, bit[MAXN];
pii pt[MAXN];

bool exi[MAXN];
void upd(ll x) {
    if (exi[x]) {
        return;
    }
    exi[x] = 1;
    for (;x<MAXN;x+=-x&x) {
        bit[x]++;
    }
}

ll qry(ll x) {
    ll ret = 0;
    for (;x>0;x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;

    vector<ll> xv;
    REP (i, n) {
        cin >> pt[i].X >> pt[i].Y;
        xv.eb(pt[i].X);
    }
    sort(ALL(xv));
    xv.resize(unique(ALL(xv))-xv.begin());
    REP (i, n) {
        pt[i].X = lower_bound(ALL(xv), pt[i].X) - xv.begin() + 1;
    }

    sort(pt, pt+n, [&](pii p1, pii p2) {
        return p1.Y != p2.Y ? p1.Y > p2.Y : p1.X < p2.X;
    });
    pary(pt, pt+n);

    REP (i, n) {
        ll st = i, mi = 0, lst = pt[i].X;
        upd(pt[i].X);
        ll cnt = qry(pt[i].X - 1);
        mi = cnt * (cnt + 1) / 2;
        while (i+1 < n && pt[i+1].Y == pt[st].Y) {
            i++;
            ll sum = qry(pt[i].X-1) - qry(lst);
            upd(pt[i].X);
            lst = pt[i].X;
            mi += sum * (sum + 1) / 2;
            debug(sum);
        }
        cnt = qry(MAXN - 1) - qry(lst);
        mi += cnt * (cnt + 1) / 2;

        ll sz = qry(MAXN-1);
        debug(sz);
        ans += sz * (sz + 1) / 2 - mi;
    }

    cout << ans << endl;
    return 0;
}
