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

const ll MAXN = 100003;
const ll MAXSQ = ll(sqrt(MAXN)) + 5;

ll n,m,l,r;
ll k,t;
ll s[MAXN];
ll cnt[MAXN]; //每個數字出現次數
ll num[MAXN]; //出現i次的數字有幾個
ll ret;
vector<ll> q[MAXSQ];
vector<pi > qr(1000000);
vector<pi > ans(1000000);
// const ll k = 316;

bool cmp1(ll a,ll b){return qr[a].Y < qr[b].Y;}
bool cmp2(ll a,ll b){return qr[a].Y > qr[b].Y;}

void add(ll x){
  debug(x);
  cnt[x]++;
  num[cnt[x]]++;
  num[cnt[x]-1]--;
  ret = max(ret,cnt[x]);
}
void sub(ll x){
  debug(x);
  cnt[x]--;
  num[cnt[x]]++;
  num[cnt[x]+1]--;
  if(num[cnt[x]+1]==0 && ret==cnt[x]+1)ret=cnt[x];
}

/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n>>m;
  k = ll(sqrt(n));
  t = n/k+1;
  REP(i,n)cin>>s[i];
  REP(i,m) {
    cin>>qr[i].X>>qr[i].Y;
    --qr[i].X,--qr[i].Y;
    q[qr[i].X/k].pb(i);
  }

  REP(i,t)sort(ALL(q[i]),(i&1?cmp2:cmp1));
  pary(q,q+m);

  l=0;r=-1;
  ret = 0;
  num[0] = n;
  ret = -1;
  REP(i,t){
    for(ll id:q[i]){
      debug(qr[id]);
      while(l>qr[id].X){l--;add(s[l]);}
      while(r<qr[id].Y){r++;add(s[r]);}
      while(l<qr[id].X){sub(s[l]);l++;}
      while(r>qr[id].Y){sub(s[r]);r--;}
      ans[id] = mp(ret,num[ret]);
    }
  }
  REP(i,m)cout<<ans[i].X<<' '<<ans[i].Y<<'\n';
	return 0;
}
