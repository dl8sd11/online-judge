#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
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

typedef pair<ll,ll> pdd;

ll T,n,x,y;
pdd pig[26];
ll dp[16800000];
ll pt[16800000];
vector<ll> cover[26];

ll mul(ll a,ll b,ll c){
  return (((a*b)%MOD)*c)%MOD;
}
ll myexp(ll base,ll _x){
  if(_x==1)return base;
  ll tmp = myexp(base,_x/2);
  if(_x&1)return mul(tmp,tmp,base);
  else return mul(tmp,tmp,1);
}
ll mydiv(ll a,ll b){
  return (a * myexp(b,MOD-2))%MOD;
}
pdd solve(ll x1,ll x2,ll y1,ll y2){
  if(x1>x2)swap(x1,x2),swap(y1,y2);
  if(x1==x2||x1*y2-x1*y1>=y1*x2-y1*x1)return mp(-1,-1);
  ll delta = (mul(x1,x1,x2)-mul(x2,x2,x1))%MOD;
  ll deltaA = (mul(y1,x2,1)-mul(y2,x1,1))%MOD;
  ll deltaB = (mul(x1,x1,y2)-mul(x2,x2,y1))%MOD;
  if(delta<0)delta+=MOD;
  if(deltaA<0)deltaA+=MOD;
  if(deltaB<0)deltaB+=MOD;
  return mp(mydiv(deltaA,delta),mydiv(deltaB,delta));
}
ll getans(ll status){
  if(dp[status]!=-1)return dp[status];
  ll idx = __lg(status&-status);
  if(cover[idx].empty())return dp[status] = getans(status-(1<<idx)) + 1;
  ll mn = INF;
  for(auto fil:cover[idx]){
    ll tmp = getans(status&((1<<n)-fil-1));
    if(tmp<mn){
      mn = tmp;
      pt[status] = status&((1<<n)-fil-1);
    }
  }
  return dp[status] = mn + 1;
}
int main()
{
  IOS();
  cin>>T;
  while(T--){
    MEM(dp,-1);
    cin>>n;
    REP(i,n){
      cin>>x>>y;
      pig[i] = {x,y};
    }
    REP(i,n)cover[i].clear();
    set<pdd> lines;
    REP(i,n){
      REP(j,i){
        if(i==j)continue;
        pdd ret = solve(pig[i].X,pig[j].X,pig[i].Y,pig[j].Y);
        if(ret.X!=-1) {
          lines.insert(ret);
        }
      }
    }

    for(auto para:lines) {
      debug(para);
      ll fliter = 0;
      REP(i,n){
        // tmpa +  tmpb - tmpc
        ll tmpa = mul(pig[i].X,pig[i].X,para.X);
        ll tmpb = mul(pig[i].X,para.Y,1);
        ll tmpc = pig[i].Y;
        ll dici = ((tmpa+tmpb)%MOD-tmpc) % MOD;
        if(dici<0)dici += MOD;
        if(dici== 0){
          fliter += (1<<i);
        }
      }
      debug(fliter);
      REP(i,n){
        if((1<<i)&fliter)cover[i].pb(fliter);
      }
    }
    dp[0] = 0;
    cout<<getans((1<<n)-1)<<endl;
    // ll start = (1<<n)-1;
    // while(pt[start]!=start){
    //   debug(start);
    //   start=pt[start];
    // }
    // debug(start);



  }
  debug("end");
	return 0;
}
