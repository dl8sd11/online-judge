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
#endif // brian
//}


const ll MAXN=1000;
const ll MOD=1000000007;
const ll INF=ll(1e15);

ll n;
string s[MAXN];
ll bst = -1;
bool vis[MAXN];
vector<ll> ans;

ll solve(ll idx){
  vis[idx] = 1;
  REP(i,n){
    if(i!=idx&&!vis[i]){
      if(s[idx][9]==s[i][0] && s[idx][10]==s[i][1] && s[idx][11]==s[i][2]){
        return solve(i) + 1;
      }
    }
  }
  return 1;
}

void print_ans(ll idx){
  vis[idx]=1;
  cout<<s[idx];
  REP(i,n){
    if(!vis[i]){
      if(s[idx][9]==s[i][0] && s[idx][10]==s[i][1] && s[idx][11]==s[i][2]){
        cout<<"→";
        print_ans(i);
        return;
      }
    }
  }
  cout<<'\n';
}
int main()
{
    IOS();
    cin>>n;
    REP(i,n){
      cin>>s[i];
    }

    REP(i,n){
      MEM(vis,0);
      ll tmp = solve(i);
      if(tmp > bst){
        ans.clear();
        ans.push_back(i);
        bst = tmp;
      } else if(tmp == bst){
        ans.push_back(i);
      }
    }

    cout<<bst<<endl;
    REP(i,SZ(ans)){
      MEM(vis,0);
      print_ans(ans[i]);
    }
}
