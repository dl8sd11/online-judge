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
const ll MAXN = 800002;

ll n,p,a[MAXN],ans[MAXN];
struct BIT {
    ll bit[MAXN];
    void add(ll pos,ll val) {
        pos++;
        for (;pos<MAXN;pos+=-pos&pos) {
            bit[pos] += val;
        }
    }
    ll query(ll pos) {
        ll ret = 0;
        pos++;
        for (;pos>=1;pos-=-pos&pos) {
            ret += bit[pos];
        }
        return ret;
    }
};
namespace MIN {
    BIT left,right;
    vector<ll> l,r;
    vector<ll> lv,rv;
    void solve() {
        REP (i,n) {
            lv.eb(a[i]+i);
        }
        sort(ALL(lv));
        lv.resize(unique(ALL(lv))-lv.begin());
        REP (i,n) {
            l.eb(lower_bound(ALL(lv),a[i]+i)-lv.begin());
        }

        REP (i,n) {
            rv.eb((n-i-1)+a[i]);
        }
        sort(ALL(rv));
        rv.resize(unique(ALL(rv))-rv.begin());
        REP (i,n) {
            r.eb(lower_bound(ALL(rv),(n-i-1)+a[i])-rv.begin());
        }
        debug(l);
        debug(r);

        REP (i,n) {
            right.add(l[i],1);
        }   
        REP (i,n) {
            right.add(l[i],-1);
            debug(right.query(l[i]-1));
            ans[i] = right.query(l[i]-1) + left.query(r[i]-1)+1;
            left.add(r[i],1);
        }
    }
};

namespace MAX {
    void solve() {
        vector<ll> tmp;
        REP (i,n) {
            tmp.eb(a[i]);
        }
        sort(ALL(tmp));

        REP (i,n) {
            ans[i] = lower_bound(ALL(tmp),a[i])-tmp.begin()+1;
            for (ll j=1;i-j>=0 || i+j<n;j++) {
                debug(i);
                vector<ll> v,id;
                for (ll k=0;k<=i-j;k++) {
                    v.eb(a[k]);
                }
                for (ll k=max(0LL,i-j+1);k<min(n,i+j);k++) {
                    ll cur = INF;
                    if (i+j < n) {
                        // debug(abs(k-(i+j)));
                        ll tp = abs(k-(i+j))+a[k];
                        cur = min(cur,tp);
                    }
                    if (i-j >= 0) {
                        ll tp = abs(k-(i-j))+a[k];
                        cur = min(cur,tp);
                    }
                    debug(cur,a[k],i+j);
                    assert(cur != INF);
                    v.eb(cur);
                    // v.eb(min(abs(k-(i-j)),abs(k-(i+j)))+a[k]);
                }
                for (ll k=i+j;k<n;k++) {
                    v.eb(a[k]);
                }
                sort(ALL(v));
                debug(v);
                ll mid = j + a[i];
                ll rk = lower_bound(ALL(v),mid)-v.begin()+1;
                ans[i] = max(ans[i],rk);
            }
        }
    }
};
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> p;

    vector<ll> val;
    REP (i,n) {
        cin >> a[i];
    }

  

    if (p == 1) {
        MIN::solve();
        REP (i,n) {
            cout << ans[i] << endl;
        }
    } else {
        MAX::solve();
        REP (i,n) {
            cout << ans[i] << endl;
        }
    }
    return 0;
}
