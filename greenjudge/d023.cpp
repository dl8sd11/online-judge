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

int n;
char tmp;
int st,ed;
int p[5];
int ans = 0x3f3f3f3f;
bool ch[4];
bool ansch[4];
void DFS(int idx,int cnt){
  if(idx==4){
    debug(st,ed);
    if(st==ed&&cnt<ans){
      ans = cnt;
      REP(i,4)ansch[i] = ch[i];
    }
    return;
  }
  DFS(idx+1,cnt);
  ch[idx]=1;
  st^= p[idx+1];
  DFS(idx+1,cnt+1);
  ch[idx]=0;
  st^= p[idx+1];
}
int main()
{
    IOS();
    cin>>tmp>>tmp>>n;
    st = 0,ed = 0;
    cin>>tmp>>tmp;
    REP(i,n)cin>>tmp,st*=2,st+=tmp-'0';
    cin>>tmp>>tmp;
    REP(i,n)cin>>tmp,ed*=2,ed+=tmp-'0';

    int cst = st;
    p[1] = (1<<n)-1;
    REP(i,n)p[2]*=2,p[2]+=!((i)&1);
    REP(i,n)p[3]*=2,p[3]+=((i)&1);
    REP(i,n){
      p[4]*=2;
      if(i%3==0)p[4]++;
    }

    debug(st,ed);
    DFS(0,0);
    pary(p+1,p+5);
    debug(ans);

    if(ans==0x3f3f3f3f){
      cout<<"無解"<<endl;
      return 0;
    }

    int seq[] = {3,0,1,2};
    REP(k,4){
      int i = seq[k];
      if(ansch[i]){
        cout<<"P"<<i+1<<":";
        cst ^= p[i+1];
        int tmpp = cst;
        int h = 1<<(n-1);
        REP(j,n){
          cout<<((h&tmpp)!=0);
          h>>=1;
        }
        cout<<endl;
      }
    }
}
