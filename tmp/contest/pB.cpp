#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
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

const ll MAXN = 40;
ll t,n,l,r,w,v;
pii wv[MAXN];
/********** Main()  function **********/
vector<pii> cob1;
vector<pii> cob2;
void dfs1(ll idx,ll wsum,ll vsum){
  debug(idx);
  if(idx==n/2){
    cob1.pb({wsum,vsum});
    return;
  }
  dfs1(idx+1,wsum+wv[idx].X,vsum+wv[idx].Y);
  dfs1(idx+1,wsum,vsum);
}
void dfs2(ll idx,ll wsum,ll vsum){
  debug(idx);
  if(idx==n){
    cob2.pb({wsum,vsum});
    return;
  }
  dfs2(idx+1,wsum+wv[idx].X,vsum+wv[idx].Y);
  dfs2(idx+1,wsum,vsum);
}
struct node{
  ll val;
  ll L,R;
  node *lc,*rc;
  node(ll vali,ll li,ll ri,node *lci,node *rci):val(vali),L(li),R(ri),lc(lci),rc(rci){
    if(lc)val=max(lc->val,rc->val);
  }
};
node *build(ll L,ll R){
  if(L == R-1) return new node(cob2[L].Y,L,R,0,0);
  ll mid = (L+R)/2;
  return new node(0,L,R,build(L,mid),build(mid,R));
}

ll query(ll L,ll R,node *nd){
  if(L==nd->L&&R==nd->R)return nd->val;
  ll mid = (nd->L+nd->R)/2;
  if(L>=mid)return query(L,R,nd->rc);
  else if(R<=mid) return query(L,R,nd->lc);
  else {
    return max(query(L,mid,nd->lc),query(mid,R,nd->rc));
  }
}

int main()
{
  IOS();
  cin>>t;
  while(t--){
    cin>>n>>l>>r;
    cob1.clear();
    cob2.clear();
    REP(i,n){
      cin>>w>>v;
      wv[i] = {w,v};
    }
    dfs1(0,0,0);
    dfs2(n/2,0,0);

    sort(ALL(cob1));
    sort(ALL(cob2));
    ll ans = -1;
    node *root = build(0,cob2 .size());
    ll dl = cob2.size(), dr=cob2.size();
    debug(cob1);
    debug(cob2);

    for(auto e:cob1){
      while(dl>0&&cob2[dl-1].X+e.X>=l)dl--;
      while(dr>0&&cob2[dr-1].X+e.X>r)dr--;
      debug(dl,dr);
      if(dl==dr)continue;
      ans = max(ans,query(dl,dr,root)+e.Y);
    }
    cout<<ans<<endl;
  }
	return 0;
}
