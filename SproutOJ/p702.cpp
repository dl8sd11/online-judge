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
ll n,m;
vector<pair<ll,bool> > e[MAXN];
ll dp[MAXN];
ll dfs(ll id,ll root){

}
ll pos2id(ll i,ll j){
  return j+i*m;
}
int main()
{
  IOS();
  cin>>n>>m;
  ll f[n][m];
  pair<ll,ll> mpos = {0,0};
  REP(i,n){
    REP(j,m){
      cin>>f[i][j];
      if(f[i][j]>f[mpos.X][mpos.Y])mpos={i,j};
    }
  }

  REP(i,n){
    vector<pair<ll,ll> > far;
    REP(j,m)far.pb({j,f[i][j]});
    sort(ALL(far),[](const pair<ll,ll> &a,const pair<ll,ll> &b){return a.Y<b.Y;});
    REP(j,m-1){

      e[pos2id(i,j+1)].pb({pos2id(i,j),(f[i][j+1]==f[i][j]?0:1)});
    }
  }

  REP(j,m){
    vector<pair<ll,ll> > far;
    REP(i,n)far.pb({j,f[i][j]});
    sort(ALL(far),[](const pair<ll,ll> &a,const pair<ll,ll> &b){return a.Y<b.Y;});
    REP(i,n-1){
      e[pos2id(i,j)].pb({pos2id(i+1,j),(f[i+1][j]==f[i][j]?0:1)});
      e[pos2id(i+1,j)].pb({pos2id(i,j),(f[i+1][j]==f[i][j]?0:1)});
    }
  }
  debug(mpos);
  cout<<dfs(pos2id(mpos.X,mpos.Y))<<endl;
	return 0;
}

//Github is great
