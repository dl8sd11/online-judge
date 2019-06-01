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
const ll MAXN = 100005;

ll n,s,l,a[MAXN];
struct SEGMX {
    ll seg[MAXN*2];
    void build() {
        for (ll i=n-1;i>0;i--) {
            seg[i] = max(seg[i<<1],seg[i<<1|1]);
        }
    }
    void upd(ll pos,ll val) {
        for (seg[pos+=n]=val;pos>1;pos>>=1) {
            seg[pos>>1] = max(seg[pos],seg[pos^1]);
        }
    }
    ll query(ll L,ll R) {
        ll ret = -INF;
        for (L+=n,R+=n;L<R;L>>=1,R>>=1) {
            if (L&1) {
                ret = max(ret,seg[L++]);
            }
            if (R&1) {
                ret = max(ret,seg[--R]);
            }
        }
        return ret;
    }
}mx;

struct SEGMN {
    ll seg[MAXN*2];
    void build() {
        for (ll i=n-1;i>0;i--) {
            seg[i] = min(seg[i<<1],seg[i<<1|1]);
        }
    }
    void upd(ll pos,ll val) {
        for (seg[pos+=n]=val;pos>1;pos>>=1) {
            seg[pos>>1] = min(seg[pos],seg[pos^1]);
        }
    }
    ll query(ll L,ll R) {
        ll ret = INF;
        for (L+=n,R+=n;L<R;L>>=1,R>>=1) {
            if (L&1) {
                ret = min(ret,seg[L++]);
            }
            if (R&1) {
                ret = min(ret,seg[--R]);
            }
        }
        return ret;
    }
}mn,dp;

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> s >> l;
    REP (i,n) {
        cin >> a[i];
        mx.seg[i+n] = a[i];
        mn.seg[i+n] = a[i];
    }
    mx.build();
    mn.build();
    MEM(dp.seg,INF);

    REP (i,n) {
        ll L = -1, R = i;
        while (L < R - 1) {
            ll mid = (L + R) >> 1;
            debug(mid,mx.query(mid,i+1),mn.query(mid,i+1));
            if (mx.query(mid,i+1)-mn.query(mid,i+1) > s) {
                L = mid;
            } else {
                R = mid;
            }
        }
        debug(i,R);
        if (i - R + 1 >= l) {
            if (R == 0) {
                dp.upd(i,1);
            } else {
                dp.upd(i,dp.query(R-1,i-l+1)+1);
            }
        }
    }

    if (dp.seg[n*2-1] >= INF) {
        cout << -1 << endl;
    } else {
        cout << dp.seg[n*2-1] << endl;
    }
    return 0;
}
