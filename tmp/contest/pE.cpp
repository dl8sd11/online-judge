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
const ll MAXN = 1e5 + 7;

ll t,q,l1,r1,l2,r2;
string a,b;

vector<ll> hasha(MAXN,0);
vector<ll> hashb(MAXN,0);

void rolling_hash(string s,ll c,ll md,vector<ll> &pre_hash){
  ll sum = 0;
  ll times = 1;
  REP1(i,ll(s.size())){
    sum+=(s[i-1]*times)%md;
    sum%=md;
    pre_hash[i] = sum;
    times = (times*c)%md;
  }
}

ll myexp(ll base,ll power){
  if(power== 0)return 1;
  if(power==1)return base;
  if(power>1){
    ll tmp = myexp(base,power/2);
    if(power&1)return (((tmp*tmp)%MOD)*base)%MOD;
    else return (tmp*tmp)%MOD;
  } else {
    ll rev = myexp(base,MOD-2);
    debug(rev);

    return myexp(rev,-power);
  }
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>t;
  while(t--){
    cin>>a>>b;
    cin>>q;
    rolling_hash(a,880301,MOD,hasha);
    rolling_hash(a,880301,MOD,hashb);
    debug(hasha);
    debug(hashb);
    REP(i,q){
      cin>>l1>>r1>>l2>>r2;
      l1++,l2++,r1++,r2++;

      ll lensa = r1-l1+1;
      ll lensb = r2-l2+1;

      ll ret;
      if(lensb>lensa){
        debug(lensa,lensb);
        ret = 0;
        ll match = hasha[r1]-hasha[l1-1];
        if(match<0)match+=MOD;
        debug(l2,l1,myexp(880301,l2-l1));
        match*=myexp(880301,l2-l1);
        match%=MOD;
        REP(j,lensb-lensa+1){
          ll part = hashb[l2+lensa+j-1]-hashb[l2+j-1];
          if(part<0)part+=MOD;
          debug(match,part);
          if(part==match)ret++;
          match = (match * 880301)%MOD;
        }
      } else {
        debug(lensb,lensa);
        ret = 0;
        ll match = hashb[r2]-hashb[l2-1];
        if(match<0)match+=MOD;
        match*=myexp(880301,l1-l2);
        match%=MOD;
        REP(j,lensa-lensb+1){
          ll part = hashb[l1+lensb+j-1]-hashb[l1+j-1];
          if(part<0)part+=MOD;
          debug(match,part);
          if(part==match)ret++;
          match = (match * 880301)%MOD;
        }
      }
      cout<<ret<<endl;
    }
  }
	return 0;
}
