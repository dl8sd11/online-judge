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

ll p,n;
ll w[20][20];
bool vis[20];
ll solve(ll idx){
  ll ret = 0;
  for(ll i=0;i<n;i++)if(!vis[i]){
    vis[i] = 1;
    ret = max(ret,solve(idx+1) + w[idx][i]);
    vis[i] = 0;
  }
  return ret;
}
int main()
{
    IOS();
    cin>>p;
    REP1(caseno,p){
      cin>>n;
      REP(i,n)REP(j,n){
        cin>>w[i][j];
      }
      ll sum1 = 0;
      REP(i,n){
        ll ret = 0;
        REP(j,n)ret = max(ret,w[i][j]);
        sum1 += ret;
      }

      ll sum2 = 0;
      REP(j,n){
        ll ret = 0;
        REP(i,n)ret = max(ret,w[i][j]);
        sum2 += ret;
      }

      FILL(vis,0);

      cout<<"第"<<caseno<<"組測試資料結果\n";
      cout<<"(1) 讓所有先生都最滿意的「速配程度」總分為"<<sum1<<"分\n";
      cout<<"(2) 讓所有小姐都最滿意的「速配程度」總分為"<<sum2<<"分\n";
      cout<<"(3) 完滿結局最高「速配程度」總分為"<<solve(0)<<"分\n";

    }
}
