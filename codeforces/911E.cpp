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

int n,k;
queue<int> a,b;
stack<int> s;
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n>>k;
  bool p[n+3] ={};
  REP (i,k) {
    int tmp;
    cin>>tmp;
    p[tmp] = 1;
    b.push(tmp);
    a.push(tmp);
  }

  int idx = 1;
  while (a.size()) {
    debug(a.size());
    if (s.empty()) {
      s.push(a.front());
      a.pop();
    } else {
      if (a.front() > s.top()) {
        cout<<-1<<endl;
        return 0;
      } else {
        s.push(a.front());
        a.pop();
      }
    }
    while (s.size()) {
      if (s.top() == idx) {
        s.pop();
        idx++;
      } else break;
    }
  }

  while (b.size()) {
    cout<<b.front()<<' ';
    b.pop();
  }
  while (s.size()) {
    for (int i=s.top()-1;i>=idx;i--) {
      if (!p[i]) {
        cout<<i<<' ';
        p[i] = 1;
      }
    }
    idx = s.top() + 1;
    s.pop();
  }
  for (int i=n;i>=idx;i--) {
    if (!p[i]) {
      cout<<i<<' ';
      p[i] = 1;
    }
  }
	return 0;
}
