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

string a;

char hh [5][5] = {{'L','O','V','E','I'},{'S','A','M','N','Y'},{'P','D','R','T','H'}\
,{'G','B','C','F','K'},{'Q','U','W','X','Z'}};
int x[27],y[27];

void build_rev(){
  for(int cur=0;cur<26;cur++){
    char tg = char(cur+'A');
    if(tg == 'J')continue;
    REP(i,5)REP(j,5)if(hh[i][j]==tg)x[cur]=i,y[cur]=j;
  }
}

char sf1(ll px,ll py){
  if(py==4)return hh[px][0];
  else return hh[px][py+1];
}

char sf2(ll px,ll py){
  if(px==4)return hh[0][py];
  else return hh[px+1][py];
}
int main()
{
    IOS();
    build_rev();
    cin>>a;

    REP(i,SZ(a))if(a[i]=='J')a[i]='I';

    vector<char> input;
    ll idx = 0;
    while(idx!=SZ(a)){
      if(idx==SZ(a)-1){
        input.push_back(a[idx]);
        input.push_back('X');
        idx+=1;
      } else {
        if(a[idx]==a[idx+1]){
          input.push_back(a[idx]);
          input.push_back('X');
          idx++;
        } else {
          input.push_back(a[idx]);
          input.push_back(a[idx+1]);
          idx+=2;
        }
      }
    }

    for(int i=0;i<SZ(input);i+=2){
      int a = input[i]-'A';
      int b = input[i+1]-'A';

      if(x[a]==x[b]){
        cout<<sf1(x[a],y[a]);
        cout<<sf1(x[b],y[b]);
      } else if(y[a]==y[b]){
        cout<<sf2(x[a],y[a]);
        cout<<sf2(x[b],y[b]);
      } else {
        cout<<hh[x[b]][y[a]];
        cout<<hh[x[a]][y[b]];
      }
    }
    cout<<endl;
}
