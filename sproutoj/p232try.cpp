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
const ll MAXN = 3e5;

ll c[MAXN],t,tmp,n,m,q,id,val,tsum;

const ll k = 450;
vector<ll> h,l;
bool adj[460][100000];
ll sum[10000];
ll delta[100000];
ll addt[10000];
ll mul[460][460];
ll mulsb[460][10000];
string cmd;
vector<ll> p[10000];
int main()
{
  IOS();

  cin>>n>>m>>q;
  REP(i,n)cin>>c[i];
  REP(i,m){
    cin>>t;
    while(t--){
      cin>>tmp;
      tmp--;
      p[i].pb(tmp);
      sum[i]+=c[tmp];
    }
    sort(ALL(p[i]));
    if(p[i].size()>k)h.pb(i);
    else l.pb(i);
  }


  for(auto _id:h){
    for(auto hum:p[_id])adj[_id][hum]=1;
  }

  for(auto i:h){
    for(auto j:h){
      if(i==j)mul[i][j]=p[i].size();
      else{
        ll cnt = 0;
        ll x=0,y=0;
        while(x<p[i].size()&&y<p[j].size()){
          if(p[i][x]>p[j][y])y++;
          else if(p[i][x]<p[j][y])x++;
          else x++,y++,cnt++;
        }
        mul[i][j] = mul[j][i] = cnt;
      }
    }
  }
  pary(mul[0],mul[0]+2);
  for(auto i:h){
    for(auto j:l){
      ll cnt = 0;
      for(auto x:p[j])if(adj[i][x])cnt++;
      mulsb[i][j] = cnt;
    }
  }

  while(q--){
    cin>>cmd>>id;
    id--;
    if(cmd[0]=='Q'){
      if(p[id].size()>k){
        cout<<sum[id]<<endl;
      } else {
        ll ret = sum[id];
        for(auto i:h) {
          ret+=addt[i]*mulsb[i][id];
        }
        for(auto i:p[id])ret+=delta[i];
        cout<<ret<<endl;
      }
    } else {
      cin>>val;
      if(p[id].size()>k){
        for(auto i:h)sum[i]+=val*mul[i][id];
        addt[id]+=val;
      } else {
        for(auto i:h)sum[i]+=mulsb[i][id]*val;
        for(auto i:p[id])delta[i]+=val;
      }
    }
  }
	return 0;
}
