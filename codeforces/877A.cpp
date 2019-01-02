#include <bits/stdc++.h>
using namespace std;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define IN(A, B, C) assert( B <= A && A <= C)
#define MP make_pair
#define PB push_back
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define X first
#define Y second
#define endl '\n'
const double pi=acos(-1.0);
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef map<int,int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;

/****** Template of some basic operations *****/
template<typename T, typename U> inline void amin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void amax(T &x, U y) { if(x < y) x = y; }
/**********************************************/

void IOS(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
}
/********** Main()  function **********/
int main()
{
  IOS();
  string c;
  cin>>c;
  int cnt = 0;
  int len = int(c.length());
  for(int i=0;i<len;i++){
    if(c.substr(i,5)=="Danil") cnt++;
    if(c.substr(i,4)=="Olya") cnt++;
    if(c.substr(i,5)=="Slava") cnt++;
    if(c.substr(i,3)=="Ann") cnt++;
    if(c.substr(i,6)=="Nikita") cnt++;
    if(cnt>1)break;
  }
  if(cnt==1)
    cout<<"Yes"<<endl;
  else
    cout<<"No"<<endl;
	return 0;
}
