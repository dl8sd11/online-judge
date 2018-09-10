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

string color = "*ROYGBIPLW";
map<char,int> cm;
int garden[82];
bool out[82];
/********** Main()  function **********/
bool solve(int idx) {
  if (idx==81) {
    return true;
  }
  if (!out[idx]) {
    return solve(idx+1);
  }
  int x = idx/9;
  int y = idx%9;
  int tmp[82];
  REP (i,82) tmp[i] = garden[i];
  bool used[10]={};
  REP (i,9) {
    used[garden[x*9+i]] =1;
    used[garden[y+9*i]] = 1;
  }

  REP (i,3) {
    REP (j,3) {
      used[garden[((x/3)*3+i)*9+(y/3)*3+j]]=1;
    }
  }

  REP1 (i,9) {
    if (!used[i]) {
      garden[idx] = i;
      if (solve(idx+1)) return true;
      REP (u,82) garden[u] = tmp[u];
    }
  }
  return 0;
}
int main()
{
  IOS();
  REP (i,10) cm[color[i]]=i;
  char input;
  REP (i,81) {
    cin>>input;
    if (input=='*') out[i] = 1;
    garden[i] = cm[input];
  }
  pary(garden,garden+81);
  solve(0);
  pary(garden,garden+81);
  REP (i,9) {
    REP (j,9) {
      if (out[i*9+j]) cout<<color[garden[i*9+j]];
    }
    cout<<endl;
  }
	return 0;
}
