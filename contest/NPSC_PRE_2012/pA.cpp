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

ll t,n,m,nn,mm;
ll G[20][20];
ll nG[20][20];

int main()
{
    IOS();
    cin>>t;
    while (t--) {
      cin>>n>>m;
      MEM(G,0);
      MEM(nG,0);
      REP (i,m) {
        ll u,v;
        cin>>u>>v;
        G[u][v]++;
        G[v][u]++;
      }

      cin>>nn>>mm;
      REP (i,mm) {
        ll u,v;
        cin>>u>>v;
        nG[u][v]++;
        nG[v][u]++;
      }

      bool flag = 0;
      vector<ll> permu;
      REP (i,n) permu.push_back(i);
      do {
        bool tf = 0;
        REP (i,nn) {
          REP (j,i) {
            if(G[permu[i]][permu[j]] != nG[i][j]) {
              tf = true;
              break;
            }
          }
          if(tf)break;
        }
        if(!tf){
          flag = 1;
          debug(permu);
          break;
        }
      } while(next_permutation(ALL(permu)));

      if(flag)cout<<"YES"<<endl;
      else cout<<"NO"<<endl;
    }
    debug("Hi");
}
