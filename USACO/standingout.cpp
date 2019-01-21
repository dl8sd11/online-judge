#include <bits/stdc++.h>
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
#define eb emplace_back
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

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

int n,N;
string name[MAXN];
string t;

int sa[MAXN];
int tmp[2][MAXN];
int c[MAXN];
int lcpa[MAXN];
int rk[MAXN];

void lcp_array(){
  int lcp = 0;
  REP(i,N)rk[sa[i]] = i;
  REP(i,N){
    if(rk[i]==0)lcpa[0]=0;
    else {
      int j = sa[rk[i]-1];
      if(lcp>0)lcp--;
      while(t[i+lcp]==t[j+lcp])lcp++;
      lcpa[rk[i]] = lcp;
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

ll ans[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
#ifndef tmd
    freopen("standingout.in","r",stdin);
    freopen ("standingout.out","w",stdout);
#endif
    cin >> n;
    REP (i,n) {
        cin >> name[i];
        t += name[i] + char(123);
    }
    N = t.size();
    suffix_array();
    lcp_array();

    ll pre = 0;
    REP (i,n) {
        REP (j,SZ(name[i])) {
            ans[i] += max(0LL,SZ(name[i]) - j - max(lcpa[rk[j+pre]],lcpa[rk[j+pre]+1]));
            debug(SZ(name[i]),j,lcpa[rk[j+pre]],lcpa[rk[j+pre]+1]);
        }
        pre += SZ(name[i]) + 1LL;
    }
    debug(t);
    pary(sa,sa+N);
    pary(rk,rk+N);
    pary(lcpa,lcpa+N);

    REP (i,n) {
        cout << ans[i] << " \n"[i==n-1];
    }

    return 0;
}
