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
  int n;
  cin>>n;
  while (n) {
    string tmp;
    cin>>tmp;
    int m = int(tmp.size());
    int ma[n+2][m+2] = {};
    pair<int,int> root;
    REP (i,m) {
      if (tmp[i] == '.') ma[1][i+1] = 1;
      else if (tmp[i] == 'K') root.X = 1,root.Y = i+1;
      else if (tmp[i] == '@') ma[1][i+1] = 2;
    }
    for (int i=2;i<=n;i++) {
      REP (j,m) {
        char input;
        cin>>input;
        if (input == '.') ma[i][j+1] = 1;
        else if (input == 'K') root.X = i,root.Y = j+1;
        else if (input == '@') ma[i][j+1] = 2;
      }
    }

    // REP (i,n+2) {
    //   REP (j,m+2) {
    //     cout<<ma[i][j];
    //   }cout<<endl;
    // }
    queue<pair<int,int>> q;
    q.push(root);
    q.push(mp(-1,-1));
    int step = 0;
    bool flag = 0;
    while (!q.empty()) {
      //if(step>100) return 0;

      pair<int,int> cur = q.front();
      debug(cur);
      q.pop();
      if (cur.X == -1) {
        if (q.front().X == -1) break;
        step++;
        q.push(mp(-1,-1));
        continue;
      }
      if (ma[cur.X][cur.Y] == 2) {
        cout<<step<<endl;
        debug(cur);
        flag = 1;
        break;
      }
      if (ma[cur.X+1][cur.Y] == 2) q.push(mp(cur.X+1,cur.Y));
      if (ma[cur.X-1][cur.Y] == 2) q.push(mp(cur.X-1,cur.Y));
      if (ma[cur.X][cur.Y+1] == 2) q.push(mp(cur.X,cur.Y+1));
      if (ma[cur.X][cur.Y-1] == 2) q.push(mp(cur.X,cur.Y-1));
      if (ma[cur.X+1][cur.Y] == 1) q.push(mp(cur.X+1,cur.Y)),ma[cur.X+1][cur.Y] = 0;
      if (ma[cur.X-1][cur.Y] == 1) q.push(mp(cur.X-1,cur.Y)),ma[cur.X-1][cur.Y] = 0;
      if (ma[cur.X][cur.Y+1] == 1) q.push(mp(cur.X,cur.Y+1)),ma[cur.X][cur.Y+1] = 0;
      if (ma[cur.X][cur.Y-1] == 1) q.push(mp(cur.X,cur.Y-1)),ma[cur.X][cur.Y-1] = 0;
    }
    if (!flag) cout<<"= =\""<<endl;
    cin>>n;
  }
	return 0;
}
