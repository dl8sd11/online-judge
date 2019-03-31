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
const ll MAXN = 300001;


ll n,a[MAXN];
namespace MIN {
    ll seg[MAXN*2];
    void build() {
        for (ll i=n-1;i>=1;i--) {
            seg[i] = min(seg[i<<1],seg[i<<1|1]);
        }
    }

    ll query(ll l,ll r) {
        ll ret = INF;
        for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
            if (l & 1) {
                ret = min(ret,seg[l++]);
            }
            if (r & 1) {
                ret = min(ret,seg[--r]);
            }
        }
        return ret;
    }
};

namespace MAX {
    ll seg[MAXN*2];
    void build() {
        for (ll i=n-1;i>=1;i--) {
            seg[i] = max(seg[i<<1],seg[i<<1|1]);
        }
    }

    ll query(ll l,ll r) {
        ll ret = -1;
        for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
            if (l & 1) {
                ret = max(ret,seg[l++]);
            }
            if (r & 1) {
                ret = max(ret,seg[--r]);
            }
        }
        return ret;
    }
};
vector<ll> val;

ll find_right(ll idx) {
    ll L = idx,R = n;
    while (L < R - 1) {
        ll mid = (L + R) >> 1;
        if (MIN::query(idx,mid+1) < a[idx]) {
            R = mid;
        } else {
            L = mid;
        }
    }
    return R;
}

vector<ll> pos[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> a[i];
        val.eb(a[i]);
    }

    sort(ALL(val));
    val.resize(unique(ALL(val))-val.begin());
    REP (i,n) {
        a[i] = lower_bound(ALL(val),a[i])-val.begin();
        pos[a[i]].eb(i);
        MIN::seg[i+n] = MAX::seg[i+n] = a[i];
    }

    MIN::build();
    MAX::build();

    ll ptr = 0,ans = 0;
    while (ptr < n) {
        ll rgt = find_right(ptr);
        ll mval = MAX::query(ptr,rgt);
        debug(ptr,rgt,mval);
        ptr = *prev(lower_bound(ALL(pos[mval]),rgt));
        ptr++;
        debug(ptr,n);
        ans++;
    }

    cout << ans << endl;
    return 0;
}
