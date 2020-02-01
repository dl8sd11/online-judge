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
const ll MAXN = 100003;

ll n,k,h[MAXN],bit1[1000003],bit2[1000003];

inline void add(ll pos,ll val,ll *bit) {
    for (;pos<1000003;pos+=-pos&pos) {
        bit[pos] += val;
    }
}

inline ll query(ll pos,ll *bit) {
    ll ret = 0;
    for (;pos>=1;pos-=-pos&pos) {
        ret += bit[pos];
    }
    return ret;
}

inline ll rquery(ll pos,ll *bit) {
    return query(1000002,bit) - query(pos,bit);
}
ll k2;
ll solve() {
    ll median = 0,sum = 0;
    for (ll i=20;i >= 0;i--) {
        ll pos = median + (1<<i);
        if (pos < 1000003 && sum + bit1[pos] <= k2) {
            sum += bit1[pos];
            median = pos;
        }
    }
    median++;
    ll pos = median * query(median-1,bit1) - query(median-1,bit2);
    ll neg = rquery(median,bit2) - median * rquery(median,bit1);
    return pos + neg;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;
    k2 = k/2;

    REP (i,n) {
        cin >> h[i];
        h[i]++;
    }

    pii bst;
    bst.X = INF;
    REP (i,n) {
        if (i-k >= 0) {
            add(h[i-k],-1,bit1);
            add(h[i-k],-h[i-k],bit2);
        }
        add(h[i],1,bit1);
        add(h[i],h[i],bit2);

        if (i >= k-1) {
            ll ret = solve();
            if (ret < bst.X) {
                bst.X = ret;
                bst.Y = i;
            }
        }
    }

    vector<ll> can;
    for (ll i=bst.Y-k+1;i<=bst.Y;i++) {
        can.eb(h[i]);
    }

    sort(ALL(can));

    for (ll i=bst.Y-k+1;i<=bst.Y;i++) {
        h[i] = can[SZ(can)/2];
    }

    cout << bst.X << endl;
    REP (i,n) {
        cout << h[i]-1 << endl;
    }
    return 0;
}
