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
const ll MAXN = (ll)1e5 + 7;
const ll MAXlg = __lg(MAXN)+2;
ll n,k;
string s;
char a[MAXN];
bool cs[27];
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n>>k>>s;

  for(auto c:s) cs[c-'a']=1;
  ll mc = -1;
  ll minc = 29;
  REP(i,26)if(cs[i]){
    minc=i;
    break;
  }
  if(k>n) {
    cout<<s;
    for(ll i=0;i<k-n;i++)cout<<char(minc+'a');
    return 0;
  }
  REP(i,26)if(cs[i])mc=i;
  ll i;
  for(i=min(n-1,k-1);i>=0;i--) {
    if(s[i]-'a'!=mc)break;
  }
  debug(i);
  for(ll j=s[i]-'a'+1;j<26;j++) {
    if(cs[j]) {
      debug(j);
      a[i] = j+'a';
      break;
    }
  }
  debug(a[i]);
  for(ll j=0;j<i;j++)a[j]=s[j];
  debug(a[i]);
  for(ll j=i+1;j<k;j++) {
    a[j]=minc+'a';
  }
  REP(j,k)cout<<a[j];
	return 0;
}
