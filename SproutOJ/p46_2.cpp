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

int main()
{
  IOS();
  int t;
  cin>>t;
  while (t--) {
    int n;
    cin>>n;
    queue<pair<int,int> > p[3];
    int status[n][n] = {};
    bool visited[3][n+2][n+2];
    REP (u,3) {
      REP (i,n+2) {
        visited[u][i][0] = 1;
        visited[u][0][i] = 1;
        visited[u][n+1][i] = 1;
        visited[u][i][n+1] = 1;
      }
    }
    int cnt[8] = {};
    REP (i,3) {
      char color;
      int a,b,j;
      cin>>color;
      cin>>a>>b;
      if (color == 'Y') j = 0;
      else if (color == 'B') j = 1;
      else  j = 2;
      visited[j][a+1][b+1] = 1;
      p[j].push(mp(a+1,b+1));
      p[j].push(mp(-1,-1));
      j*=2;
      if (!j) j++;
      status[a][b] = j;
      cnt[status[a][b]]++;
    }
    int tg;
    char tmp;
    cin>>tmp;
    if (tmp == 'R') tg = 4;
    else if (tmp == 'Y') tg = 1;
    else if (tmp == 'B') tg = 2;
    else if (tmp == 'O') tg = 5;
    else if (tmp == 'P') tg = 6;
    else if (tmp == 'G') tg = 3;
    else tg = 7;
    int ans = 0;
    while (p[0].size()||p[1].size()||p[2].size()) {
      debug(p[0].size());
      REP (i,3) {
        while (p[i].size()) {
          debug(i);
          pair<int,int> cur = p[i].front();
          p[i].pop();
          debug(p[i].size());
          int cx = cur.X;
          int cy = cur.Y;
          if (cx < 0) {
            p[i].push(mp(-1,-1));
            if (p[i].front().X < 0) p[i].pop();
            break;
          }
          cnt[status[cx-1][cy-1]]--;
          status[cx-1][cy-1]+= !i?i+1:i*2;
          cnt[status[cx-1][cy-1]]++;
          REP (j,9) {
            int dx = cx;
            int dy = cy;
            if (j<3) dx--;
            else if (j>=6) dx++;
            if (j%3 == 0) dy++;
            else if (j%3 == 2) dy--;
            if (!visited[i][dx][dy]) {
              p[i].push(mp(dx,dy));
              visited[i][dx][dy] = 1;
            }
          }
        }
      }
      ans = max(ans,cnt[tg]);
    }
    cout<<ans<<endl;
  }
	return 0;
}
