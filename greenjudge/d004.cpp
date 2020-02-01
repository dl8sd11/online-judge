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
typedef double lf;
typedef pair<ll,ll> ii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define FILL(i,n) memset(i,n,sizeof i)
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
#endif // brian
//}


const ll MAXn=1e5+5,MAXlg=__lg(MAXn)+2;
const ll MOD=1000000007;
const ll INF=ll(1e15);

bool st[6][6];
bool pre[6][6];
char c;

ll dx[8] = {-1,0,1,-1,1,-1,0,1};
ll dy[8] = {-1,-1,-1,0,0,1,1,1};
void copy(){
  REP(i,5)
    REP(j,5)
      st[i][j] = pre[i][j];
}
bool valid(ll x,ll y){
  return (x>=0&&x<5)&&(y>=0&&y<5);
}
ll cnt(ll x,ll y){
  ll ret = 0;
  REP(i,8){
    if(valid(x+dx[i],y+dy[i])&&st[x+dx[i]][y+dy[i]])ret++;
  }
  return ret;
}

ll sum(){
  ll ret = 0;
  REP(i,5)REP(j,5)ret+=st[i][j];
  return ret;
}
int main()
{
    IOS();
    REP(i,5){
      REP(j,5){
        cin>>c;
        if(c=='1')st[i][j] = 1;
        if(j!=4)cin>>c;
      }
    }

    REP(i,5)pary(st[i],st[i]+5);

    for(ll gen=2;gen<=5;gen++){
      REP(i,5){
        REP(j,5){
          if(st[i][j]){
            ll alive = cnt(i,j);
            if(alive<=1){
              pre[i][j] = 0;
            } else if(alive <= 3){
              pre[i][j] = 1;
            } else {
              pre[i][j] = 0;
            }
          } else {
            if(cnt(i,j) == 3)pre[i][j] = 1;
            else pre[i][j] = 0;
          }
        }
      }
      copy();
      cout<<"第"<<gen<<"代: "<<sum()<<"個細胞存活"<<endl;
      REP(i,5){
        REP(j,5){
          cout<<st[i][j]<<",\n"[j==4];
        }
      }
    }
}
