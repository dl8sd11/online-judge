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
const ll MAXN = 5003;

ll n,q;
ll cnt[MAXN];
ll o[MAXN],t[MAXN],l[MAXN],r[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> q;
    REP (i,q) {
        cin >> l[i] >> r[i];
        for (ll j=l[i];j<=r[i];j++) {
            cnt[j]++;
        }
    }

    ll sum = 0;
    REP1 (i,n) {
        if (cnt[i] == 1) {
            o[i]++;
            o[i] += o[i-1];
        } else if (cnt[i] == 2) {
            t[i]++;
            t[i] += t[i-1];
        }
        if (cnt[i]) {
            sum++;
        }
    }

    ll ans = 0;
    REP (i,q) {
        REP (j,q) {
            if (i != j) {
                ll tmp =  o[r[i]] - o[l[i]-1];
                tmp += o[r[j]] - o[l[j]-1];
                if (max(l[i],l[j]) <= min(r[i],r[j])) {
                    tmp += t[min(r[i],r[j])] - t[max(l[i],l[j])-1];
                }
                debug(tmp);
                ans = max(ans,sum-tmp);
            }
        }
    }

    cout << ans << endl;
    return 0;
}
