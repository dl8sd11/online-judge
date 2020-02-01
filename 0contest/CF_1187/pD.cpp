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
const ll MAXN = 300005;


ll t, n, a[MAXN], b[MAXN];
namespace SEG {
    ll dt[MAXN*2];
    void build() {
        for (ll i=n-1;i>0;i--) {
            dt[i] = min(dt[i<<1], dt[i<<1|1]);
        }
    }

    void chg(ll pos, ll val) {
        for (dt[pos+=n]=val;pos>1;pos>>=1) {
            dt[pos>>1] = min(dt[pos], dt[pos^1]);
        }
    }

    ll qry(ll l, ll r) {
        ll ret = INF;
        for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
            if (l&1) {
                ret = min(ret, dt[l++]);
            }
            if (r&1) {
                ret = min(ret, dt[--r]);
            }
        }
        return ret;
    }
}
vector<ll> app[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
        cin >> n;
        REP (i,n) {
            cin >> a[i];
            SEG::dt[i+n] = a[i];
        }
        REP (i,n) {
            cin >> b[i];
        }
        RREP (i,n-1) {
            app[a[i]].eb(i);
        }
        SEG::build();

        bool flag = true;
        REP (i, n) {
            if (app[b[i]].size()) {
                ll cur = app[b[i]].back();
                app[b[i]].pop_back();
                flag &= SEG::qry(0,cur+1) == b[i];
                SEG::chg(cur, INF);
            } else {
                flag = false;
            }
        }
        REP1 (i,n) {
            app[i].clear();
        }

        if (flag) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

    }
    return 0;
}
