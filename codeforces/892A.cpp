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
#define mp make_pair
#define pb push_back
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
typedef long long ll;

void IOS(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
}

/********** Main()  function **********/
int main()
{
  IOS();
  ll n;
  cin>>n;
  ll sum = 0;
  REP(i,n) {
    ll tmp;
    cin>>tmp;
    sum += tmp;
  }
  vector<ll> v;
  REP(i,n) {
    ll tmp;
    cin>>tmp;
    v.pb(tmp);
  }
  sort(all(v));
  ll vsize = ll(v.size());
  if (sum > v[vsize - 1] + v[vsize - 2]) {
    cout<<"No"<<endl;
  } else {
    cout<<"Yes"<<endl;
  }

	return 0;
}
