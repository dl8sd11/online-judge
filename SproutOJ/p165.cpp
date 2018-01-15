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
int t,n,m,a,b;
vector<int> e[MAXN];
int d[MAXN];
priority_queue<int,vector<int>,greater<int> > to;
bool visit[MAXN];
stringstream ss;
void clearQueue() {
  priority_queue<int,vector<int>,greater<int> > empty;
  swap(to,empty);
}
int main()
{
  IOS();
  cin>>t;
  while (t--) {
    ss = stringstream();
    clearQueue();
    cin>>n>>m;
    REP (i,n) e[i].clear();
    MEM(d,0);
    MEM(visit,0);
    REP (i,m) {
      cin>>a>>b;
      e[a].pb(b);
      d[b]++;
    }
    REP (i,n) if (d[i]==0) {
      to.push(i);
      visit[i]=1;
    }
    while (to.size()) {
      int now = to.top();
      to.pop();
      ss<<now<<' ';
      for (auto v:e[now])
        if(--d[v]<=0&&!visit[v]) {
          to.push(v);
          visit[v] = 1;
        }
    }
    int i,out;
    debug(ss.str());
    bool fo = 1;
    for (i=0;i<n;i++) if(!visit[i])break;
    if (i==n) while(ss>>out) {
      if (fo) {
        cout<<out;
        fo = 0;
      }
      else cout<<' '<<out;
    }
    else cout<<"QAQ";
    cout<<endl;
  }
	return 0;
}
