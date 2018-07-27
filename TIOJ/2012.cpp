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
const ll MAXN = 603;

ll t,n;
__float128 matrix[MAXN][MAXN];
__float128 x[MAXN];
double c;

void gaussian_elimination()
{
  for(ll i=0;i<n;i++) { //pivoting
    for(ll j=i+1; j<n; j++) {
      if(matrix[j][i] > matrix[i][i]) {
        for(ll k=i;k<=n; k++) swap(matrix[i][k],matrix[j][k]);
        break;
      }
    }
    if(matrix[i][i] == 0)continue;
    c = matrix[i][i];
    for(ll k=i;k<=n;k++) matrix[i][k] /= c;

    for(ll j=i+1;j<n;j++){
      if(matrix[j][i] != 0) {
        c = matrix[j][i];
        for(ll k=i;k<=n;k++)
          matrix[j][k] -= matrix[i][k] * c;
      }
    }
  }
}

void back_substitution()
{
  for(ll i=n-1;i>=0;i--) {
    c = 0;
    for (ll k=i+1;k<n;k++) c += matrix[i][k] * x[k];
    x[i] = (matrix[i][n] - c) / matrix[i][i];
  }
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>t;
  while(t--){
    cin>>n;
    double tmp;
    REP(i,n)REP(j,n+1)cin>>tmp,matrix[i][j] = tmp;
    gaussian_elimination();
    back_substitution();
    REP(i,n)cout<<fixed<<setprecision(10)<<double(x[i])<< '\n';
  }
	return 0;
}
//高斯消去
