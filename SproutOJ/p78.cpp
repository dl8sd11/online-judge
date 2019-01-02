#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
typedef pair<ll, ll> pi;
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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll INF = (ll)1e18 + 7;
const ll MOD = 1000000007;
const ll MAXN = 3e5;
ll g[6];
int main()
{
  IOS();
  ll sum = 0;
  REP(i,6) cin>>g[i];
  REP(i,6) sum += g[i];
  while (sum) {
    debug(sum);
    ll ans = 0;
    ans += g[5];
    debug(ans);
    ans += g[4];
    debug(ans);
    g[0] -= 11 * g[4];
    if (g[0] < 0) g[0] = 0;
    ans += g[3];
    debug(ans);
    ll sp = 20 * g[3];
    if (g[1] >= sp/4) {
      g[1] -= sp/4;
      sp = 0;
    } else {
      sp -= g[1] * 4;
      g[1] = 0;
    }
    g[0] -= sp;
    if (g[0] < 0) g[0] = 0;
    // REP(j,6) cout<<g[j]<<' ';
    // cout<<endl;
    ll ts;
    ans += ceil(g[2] / 4.0);
    ts = (4 - g[2] % 4) * 2 - 1;
    if (ts > 5) ts = 0;
    debug(ans);
    sp = 36 - (g[2] % 4)*9;
    if (sp == 36) sp = 0;
    if (g[1] >= ts) {
      g[1] -= ts;
      sp -= ts * 4;
    } else {
      sp -= g[1] * 4;
      g[1] = 0;
    }
    g[0] -= sp;
    if (g[0] < 0) g[0] = 0;
    ans += ceil(g[1] / 9.0);
    debug(ans);
    sp = 36;
    sp -= g[1] % 9 * 4;
    if (sp == 36) sp = 0;
    g[0] -= sp;
    if (g[0] < 0) g[0] = 0;
    ans += ceil(g[0] / 36.0);
    debug(ans);
    cout<<ans<<endl;
    sum = 0;
    REP(i,6) cin>>g[i];
    REP(i,6) sum += g[i];
    debug(sum);
  }
	return 0;
}
