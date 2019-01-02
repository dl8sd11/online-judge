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


const ll MAXn=1e5+5,MAXlg=__lg(MAXn)+2;
const ll MOD=1000000007;
const ll INF=ll(1e15);


string s1,s2;
ll dp[30][30];
pii source[30][30];
ll lcs(ll idx1,ll idx2){
  if(idx1==-1||idx2==-1)return 0;
  if(dp[idx1][idx2]!=-1)return dp[idx1][idx2];
  if(s1[idx1] == s2[idx2]){
    ll ret = lcs(idx1-1,idx2-1)+1;
    if(ret > dp[idx1][idx2]){
      dp[idx1][idx2] = ret;
      source[idx1][idx2] = make_pair(idx1-1,idx2-1);
    }
  }
  ll ret = lcs(idx1-1,idx2);
  if(ret > dp[idx1][idx2]){
    dp[idx1][idx2] = ret;
    source[idx1][idx2] = make_pair(idx1-1,idx2);
  }

  ret = lcs(idx1,idx2-1);
  if(ret > dp[idx1][idx2]){
    dp[idx1][idx2] = ret;
    source[idx1][idx2] = make_pair(idx1,idx2-1);
  }
  return dp[idx1][idx2];
}
vector<char> ans;
void prt(ll idx1,ll idx2){
  if(idx1==-1||idx2==-1)return;
  if(source[idx1][idx2].first == idx1-1 && source[idx1][idx2].second == idx2 - 1)ans.pb(s1[idx1]);
  prt(source[idx1][idx2].first,source[idx1][idx2].second);
}
int main()
{
    IOS();
    while(cin>>s1>>s2){
      MEM(dp,-1);
      ll len = lcs(SZ(s1)-1,SZ(s2)-1);
      // baecad accbadcb = acad
      ans.clear();
      prt(SZ(s1)-1,SZ(s2)-1);
      cout<<s1<<" "<<s2<<" = ";
      for(ll i=SZ(ans)-1;i>=0;i--)cout<<ans[i];
      if(SZ(ans)==0)cout<<0;
      cout<<endl;
    }

}
