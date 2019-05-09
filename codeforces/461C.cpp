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
const ll MAXN = 100001;

ll n,q,cmd,p,l,r,edg,tail,rev;

namespace SEG {
    ll seg[MAXN*4];
    ll N;
    void build() {
        for (ll i=N-1;i>0;i--) {
            seg[i] = seg[i<<1] + seg[i<<1|1];
        }
    }

    void add(ll pos,ll val) {
        for (seg[pos+=N]+=val;pos>1;pos>>=1) {
            seg[pos>>1] = seg[pos] + seg[pos^1];
        }
    }

    ll query(ll l,ll r) {
        ll ret = 0;
        for (l+=N,r+=N;l<r;l>>=1,r>>=1) {
            if (l&1) {
                ret += seg[l++];
            }
            if (r&1) {
                ret += seg[--r];
            }
        }
        return ret;
    }
}
ll sft(ll dis) {
    return rev ? tail- dis : edg + dis;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> q;

    SEG::N = n*2;
    REP (i,n) {
        SEG::seg[i+SEG::N] = 1;
    }
    SEG::build();
    edg = 0;
    tail = n;
    while (q--) {
        cin >> cmd;
        if (cmd == 1) {
            cin >> p;
            debug(edg,tail,sft(p));
            if (sft(p) <= (edg+tail)>>1) {
                ll sz = rev ? tail - p - edg : p;
                REP (i,sz) {
                    ll val = SEG::seg[edg+i+SEG::N];
                    SEG::add(edg+i,-val);
                    SEG::add(edg+sz-i+sz-1,val);
                }
                edg += sz;
                rev = false;
            } else {
                ll sz = rev ? p : tail - p -edg;
                debug(sz);
                REP1 (i,sz) {
                    ll val = SEG::seg[tail-i+SEG::N];
                    SEG::add(tail-i,-val);
                    SEG::add(tail-(sz)*2+i-1,val);
                }
                tail -= sz;
                rev = true;
            }
        } else {
            cin >> l >> r;
            if (rev) {
                cout << SEG::query(tail-r,tail-l) << endl;
            } else {
                cout << SEG::query(edg+l,edg+r) << endl;
            }
        }
        // pary(SEG::seg+SEG::N,SEG::seg+SEG::N*2);
    }
    return 0;
}
