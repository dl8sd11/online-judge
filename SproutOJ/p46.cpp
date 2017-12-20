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

int n;
short status[1003][1003] = {};
deque<pair<int,int> > a[3];
int cnt[8];
int tg;
void solve() {
    bool visited[3][n+3][n+3];
    MEM(visited,0);
    REP (u,3) {
      REP (i,n+2) {
        visited[u][i][0] = 1;
        visited[u][0][i] = 1;
        visited[u][n+1][i] = 1;
        visited[u][i][n+1] = 1;
      }
    }
    int ans = cnt[tg];

    while (a[0].size() || a[1].size() || a[2].size()) {
      debug(ans);
      REP (u,3) {
         debug(a[u].size());
         debug(u);
        while (a[u].size()) {
          //debug(a[u].front());
          pair<int,int> cur = a[u].front();
          debug(a[u].size());
          a[u].pop_back();
          //debug("alive");
          if (cur.X == -1) {
            a[u].pb(mp(-1,-1));
            if (a[u].front().X == -1) {
              a[u].pop_back();
              break;
            } else {
              break;;
            }
          }
          if (cur.X > 1000 || cur.X < 0) while(1) {}
          //debug("alive");
          visited[u][cur.X][cur.Y] = 1;

          int tmp = 2;
          if (u == 1) tmp = 4;
          else if (u == 2) tmp = 1;

          //debug("alive");
          cnt[status[cur.X-1][cur.Y-1]]--;
          status[cur.X-1][cur.Y-1] += tmp;
          cnt[status[cur.X-1][cur.Y-1]]++;
          //debug("alive");
          REP (i,9) {
            int dx = cur.X;
            int dy = cur.Y;

            if (i<3) dx++;
            else if(i>5) dx--;
            if (i%3 == 0) dy++;
            if (i%3 == 2) dy--;
            if (!visited[u][dx][dy]) {
              a[u].pb(mp(dx,dy));
              visited[u][dx][dy] = 1;
            }
          }
          debug(a[u].size());
          //debug(a[u].front());
        }
      }
      ans = max(ans,cnt[tg]);
    }
    cout<<ans<<endl;
}
int main()
{
  IOS();
  int t;
  cin>>t;
  while (t--) {
    cin>>n;
    MEM(status,0);
    MEM(cnt,0);


    REP (u,3) {
      char color;
      int x,y;
      cin>>color>>x>>y;


      if (color == 'Y') {
        status[x][y] = 2;
        cnt[2]++;
        a[0].pb(mp(x+1,y+1));
        a[0].pb(mp(-1,-1));
      } else if (color == 'B') {
        status[x][y] = 4;
        cnt[4]++;
        a[1].pb(mp(x+1,y+1));
        a[1].pb(mp(-1,-1));
      } else if (color == 'R') {
        status[x][y] = 1;
        cnt[1]++;
        a[2].pb(mp(x+1,y+1));
        a[2].pb(mp(-1,-1));
      }

    }
    char tmp;
    cin>>tmp;
    if (tmp == 'R') tg = 1;
    else if (tmp == 'Y') tg = 2;
    else if (tmp == 'B') tg = 4;
    else if (tmp == 'O') tg = 3;
    else if (tmp == 'P') tg = 5;
    else if (tmp == 'G') tg = 6;
    else tg = 7;
    debug(tg);
    solve();
  }

	return 0;
}
