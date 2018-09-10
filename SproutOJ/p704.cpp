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
typedef pair<int, int> pii;
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
const ll MAXN = 2001;
int n,m,q,cmd,posx,posy,c,r;
pii g[MAXN][MAXN];
pii l[2][MAXN];
int main()
{
  IOS();
  cin>>n>>m>>q;
  REP1(u,q){
    cin>>cmd>>c;
    if(cmd==1){
      cin>>posx;
      if(posx-1>0)l[0][posx-1]={u,c};
      l[0][posx]={u,c};
      if(posx+1<=n)l[0][posx+1]={u,c};
    }else if(cmd==2){
      cin>>posy;
      if(posy-1>0)l[1][posy-1]={u,c};
      l[1][posy]={u,c};
      if(posy+1<=m)l[1][posy+1]={u,c};
    }else{
      cin>>posx>>posy>>r;
      for(int i=posx-r;i<=posx+r;i++){
        if(i<=0||i>n)continue;
        for(int j=posy-r;j<=posy+r;j++){
          if(j<=0||j>m)continue;
          if((i-posx)*(i-posx)+(j-posy)*(j-posy)<=r*r)g[i][j]={u,c};
        }
      }
    }
  }
  int ans[3] = {};
  REP1(i,n){
    REP1(j,m){
      if(l[0][i].X>g[i][j].X)g[i][j]=l[0][i];
      if(l[1][j].X>g[i][j].X)g[i][j]=l[1][j];
      debug(g[i][j].Y);
      ans[g[i][j].Y]++;
    }
  }
  cout<<ans[1]<<' '<<ans[2]<<' '<<ans[0]<<endl;
	return 0;
}


// 4 5 4
// 2 1 1
// 1 2 3
// 3 1 4 5 3
// 3 2 3 4 0

// 4 5 3
// 2 1 1
// 1 2 3
// 1 1 4
