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
const ll MAXN = 1503;
ll n,m;
char p[MAXN][MAXN];
ll cnt1[2][MAXN][27];
ll cnt2[2][MAXN];
bool vis[2][MAXN];
struct pline{
  bool X;
  ll Y;
  char Z;
};
int main()
{
  IOS();
  cin>>n>>m;
  REP(i,n){
    REP(j,m){
      cin>>p[i][j];
      if(cnt1[0][i][p[i][j]-'a']++==0)cnt2[0][i]++;
      if(cnt1[1][j][p[i][j]-'a']++==0)cnt2[1][j]++;
    }
  }



  queue<pline> q; //0,x -> row
  vector<pline> ans;
  REP(i,n) {
    if(cnt2[0][i]==1)q.push({0,i,p[i][0]}),vis[0][i]=1;
  }

  REP(j,m) {
    if(cnt2[1][j]==1)q.push({1,j,p[0][j]}),vis[1][j]=1;
  }

  debug(q.size());
  pary(cnt2[0],cnt2[0]+n);
  pary(cnt2[1],cnt2[1]+m);

  REP(u,m+n){
    pline now = q.front();
    q.pop();
    ans.pb(now);

    if(!now.X){
      REP(j,m) {
        if(vis[1][j])continue;
        if(--cnt1[1][j][p[now.Y][j]-'a']==0)cnt2[1][j]--;
        if(cnt2[1][j]==1){
          debug(1,j,now.Y);
          REP(k,26)if(cnt1[1][j][k]>0)q.push({!now.X,j,char(k+'a')});
          vis[!now.X][j]=1;
        }
      }
    }else{
      REP(i,n) {
        if(vis[!now.X][i])continue;
        if(--cnt1[0][i][p[i][now.Y]-'a']==0)cnt2[0][i]--;
        if(cnt2[0][i]==1){
          debug(0,i,now.Y);
          REP(k,26)if(cnt1[0][i][k]>0)q.push({!now.X,i,char(k+'a')});
          vis[!now.X][i]=1;
        }
      }
    }
  }
  REP(i,n+m){
    pline now = ans[n+m-i-1];
    cout<<(now.X?"column ":"row ")<<now.Y+1<<" "<<(now.Z=='@'?'a':now.Z)<<endl;
  }


	return 0;
}

// 3 5
// caaza
// crbzg
// zzzzz
