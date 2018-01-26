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

ll n,t;
ll m[5];
ll state[5],bac[5];
queue<ll> Q;
unordered_set<ll> visit;

inline void comp(){
  ll ex = 1,compData = 0;
  REP (i,5) {
    compData += ex*state[i];
    ex*=51;
  }
  if (!visit.count(compData)) {
    Q.push(compData);
    visit.insert(compData);
  }

}
inline void decomp() {
  ll tmp = Q.front();Q.pop();
  ll idx = 0;
  REP (i,n) {
    state[idx++] = tmp%51;
    tmp/=51;
  }
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n;
  REP(i,n)cin>>m[i];
  cin>>t;
  comp();
  ll sz,ans=0;
  while (Q.size()) {
    debug(ans);
    sz = Q.size();
    while(sz--) {
      decomp();
      pary(state,state+n);
      REP (i,n) {
        bac[i] = state[i];
        if (state[i]==t) {
          cout<<ans<<endl;
          return 0;
        }
      }
      for (ll i=0;i<n;i++) {
        state[i] = 0;
        comp();
        state[i] = m[i];
        comp();
        state[i] = bac[i];
      }
      REP (i,n) {
        if (state[i]==0) continue;
        REP (j,n) {
          if (i==j) continue;
          if (state[i]>m[j]-state[j]) {
            state[i] -= m[j] - state[j];
            state[j] = m[j];
          } else {
            state[j] += state[i];
            state[i] = 0;
          }
          comp();
          state[i] = bac[i];
          state[j] = bac[j];
        }
      }
    }
    ans++;
  }


	return 0;
}
