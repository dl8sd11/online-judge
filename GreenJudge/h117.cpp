  #include <iostream>
  #include <algorithm>
  #include <cmath>
  #include <vector>
  #include <map>
  #include <set>
  using namespace std;
  typedef long long ll;
  typedef pair<ll, ll> pii;
  typedef pair<double,double> pdd;
  #define MEM(a, b) memset(a, (b), sizeof(a))
  #define SZ(i) ll(i.size())
  #define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
  #define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
  #define REP(i, j) FOR(i, 0, j, 1)
  #define REP1(i,j) FOR(i, 1, j+1, 1)
  #define RREP(i, j) RFOR(i, j, 0, 1)
  #define ALL(_a) _a.begin(),_a.end()
  #define mp make_pair
  #define pb push_back
  #define X first
  #define Y second
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


struct E{
  ll sdis,X,Y;
  bool operator < (const E &a)const{
    return sdis < a.sdis;
  }
  E (ll sdisi,ll Xi,ll Yi){
    sdis = sdisi;
    X = Xi;
    Y = Yi;
  }
};
const ll MAXN=1e3+5;

vector<E> edge;
ll t,n,x[MAXN],y[MAXN];
ll sz[MAXN],djs[MAXN];
void init() {
  REP (i,MAXN) djs[i] = i,sz[i]=1;
}
ll Find(ll a) {
  return (a==djs[a])?a:djs[a]=Find(djs[a]);
}
void Union(ll a,ll b) {
  if (sz[b=Find(b)]>sz[a=Find(a)])swap(a,b);
  djs[b] = a;
  sz[b] = sz[a]+sz[b];
  sz[a] = sz[b];
}
ll labs(ll a){
	return a<0?-a:a;
}

/********** Main()  function **********/
int main()
{
  IOS();
  cin>>t;
  while(t--){
  	cin>>n;
    edge.clear();
  	REP(i,n)cin>>x[i]>>y[i];
  	REP(i,n){
  		REP(j,i){
        E tmp = E(labs(x[i]-x[j])*labs(x[i]-x[j])+labs(y[i]-y[j])*labs(y[i]-y[j]),i,j);
  			edge.pb(tmp);
		  }
	  }
  	sort(ALL(edge));
  	ll ss = edge.size();
  	ll ans = 0;
    init();
  	for(ll i=0;i<ss;i++){
      debug(i);
  		if(Find(edge[i].X) != Find(edge[i].Y)){
        Union(edge[i].X,edge[i].Y);
  		  ans = max(ans,edge[i].sdis);
      }
  	}
  	cout<<int(ceil(sqrt(ans)/2))<<endl;

  }
  return 0;
}
