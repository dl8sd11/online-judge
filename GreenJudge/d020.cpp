#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<sstream>
#include<cmath>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define MEM(i,n) memset(i,n,sizeof i)
#define X first
#define Y second
#define SZ(_a) (int)_a.size()
#define ALL(_a) _a.begin(),_a.end()
#define pb push_back
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
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif


const ll MAXN=1e5+5,MAXlg=__lg(MAXN)+2;
const ll MOD=1000000007;
const ll INF=ll(1e18+7);

char u,v;
int to[27];
int vis[27];
vector<vector<int> > ans;

void save_loop(ll nd){
  debug(nd);
  int tmp = nd;
  vector<int> ret;
  while(1){
    ret.pb(tmp);
    tmp = to[tmp];
    if(tmp==nd)break;
  }
  ans.pb(ret);
}
void DFS(ll nd,ll cnt){
  debug(nd,cnt);
  if(to[nd]==-1)return;
  vis[nd] = cnt;
  if(vis[to[nd]] == vis[nd]){
    int mn = nd;
    int tmp = to[nd];
    while(tmp!=nd){
      mn = min(mn,tmp);
      tmp = to[tmp];
    }
    save_loop(mn);
  } else DFS(to[nd],cnt);
}
int main()
{
    IOS();
    MEM(to,-1);
    MEM(vis,-1);
    cout<<"存在迴圈"<<endl;
    while(cin>>u>>v){
      to[u-'A']=v-'A';
      cout<<u<<" "<<v<<" ";
    }

    REP(i,26){
      if(vis[i]==-1)DFS(i,i);
    }
    debug(ans);

    // if(ans.empty()){
    //   cout<<"不存在迴圈\n";
    // } else{
    //   cout<<"存在迴圈\n";
    //   for(int i=0;i<SZ(ans);i++){
    //     for(int j=0;j<SZ(ans[i]);j++)cout<<char('A'+ans[i][j])<<" \n"[j==SZ(ans[i])-1];
    //   }
    // }
}
