#include <iostream>
#include <cstring>
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


#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)


const ll MAXN=1e6+5;



ll t,n;
ll len,ans;
char c;
bool op[MAXN];
/********** Main()  function **********/
int main()
{
  IOS(); 
  cin>>t;
  while(t--){
    cin>>n;
    MEM(op,0);
    
    REP(i,n-1)cin>>c,op[i] = (c=='>'?1:0);

    len = 0;
    ans = 0;
    REP(i,n){
      debug(len,op[i]);
      if(op[i] == 1)len++;
      else {
	if(len!=0)ans += len*(len+1)/2;
	len = 0;
      }
    }

    cout<<ans<<endl;

  }
  return 0;
}
