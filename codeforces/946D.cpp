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
  const ll MAXN = (ll)1e5 + 7;
  const ll MAXlg = __lg(MAXN)+2;
  ll n,m,k,tmp;
  string s;
  vector<ll> sc[503];
  ll sq[503][503];
  ll dp[503][503];
  /********** Main()  function **********/
  int main()
  {
    IOS();
    cin>>n>>m>>k;
    REP(i,503)REP(j,503)sq[i][j]=INF;
    debug("HI");
    REP(i,n){
      cin>>s;
      ll sum=0;
      REP(j,m){
        if(s[j]-'0')sc[i].pb(j);
        sum+=s[j]-'0';
      }
      for(ll j=0;j<ll(sc[i].size());j++){
        //debug(sum);
        for(ll K=0;K<503;K++){
          if(sum-K-1<0)break;
          if(K+j>=sum)break;
          //debug(i,j,K,sc[i][K+j]-sc[i][j]+1);
          sq[i][sum-K-1] = min(sq[i][sum-K-1],sc[i][K+j]-sc[i][j]+1);
        }
      }
      sq[i][sum]=0;
    }
    REP(i,n)REP(j,k+1)debug(sq[i][j]);
    ll ans = INF;
    REP(j,k+1){dp[0][j]=sq[0][j];}

    REP1(i,n-1){
      REP(j,k+1){
        dp[i][j]=INF;
        REP(l,j+1)dp[i][j]=min(dp[i][j],dp[i-1][j-l]+sq[i][l]);
        //debug(i,j,dp[i][j]);
      }
    }
    REP(j,k+1)ans=min(ans,dp[n-1][j]);
    cout<<ans<<endl;

  	return 0;
  }
