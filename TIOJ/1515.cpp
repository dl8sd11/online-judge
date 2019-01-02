#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define SZ(i) int(i.size())
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
const ll MAXN = 200003;

string t;
int N;
int sa[MAXN];
int tmp[2][MAXN];
int c[MAXN];
int lcpa[MAXN];
int ans = 0;
void lcp_array(){
  int lcp = 0;
  int rank[MAXN];
  REP(i,N)rank[sa[i]] = i;
  REP(i,N){
    if(rank[i]==0)lcpa[0]=0;
    else {
      int j = sa[rank[i]-1];
      if(lcp>0)lcp--;
      while(t[i+lcp]==t[j+lcp])lcp++;
      ans = max(ans,lcp);
      lcpa[rank[i]] = lcp;
    }
  }

}
void suffix_array(){
  int A = 256;
  int *rank = tmp[0];
  int *new_rank = tmp[1];
  REP(i,A)c[i] = 0;
  REP(i,N)c[rank[i]=t[i]]++;
  REP1(i,A-1)c[i] += c[i-1];
  REP(i,N) sa[--c[rank[i]]] = i;
  for(int n=1;n<N;n*=2){
    REP(i,A)c[i] = 0;
    REP(i,N)c[rank[i]]++;
    REP1(i,A-1)c[i] += c[i-1];
    int r = 0;
    int *sa2 = new_rank;
    for(int i=N-n;i<N;i++)sa2[r++] = i;
    for(int i=0;i<N;i++)if(sa[i]>=n)sa2[r++] = sa[i]-n;
    for(int i=N-1;i>=0;i--)sa[--c[rank[sa2[i]]]] = sa2[i];
    new_rank[sa[0]] = r = 0;
    for(int i=1;i<N;i++){
      if(!(rank[sa[i]]==rank[sa[i-1]]&&sa[i-1]+n<N&&rank[sa[i]+n]==rank[sa[i-1]+n]))r++;
      new_rank[sa[i]] = r;
    }
    swap(rank,new_rank);
    if(r==N-1)break;
    A = r+1;
  }
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>N;
  cin.ignore();
  getline(cin,t);
  assert(SZ(t)==N);
  suffix_array();
  lcp_array();
  cout<<ans<<endl;
  pary(sa,sa+N);
	return 0;
}
