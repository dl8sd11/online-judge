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
const ll MAXN = int(1e3)+7;
map<char,int> colormap = {{'R',1},{'Y',2},{'O',3},{'B',4},{'P',5},{'G',6},{'D',7}};
string colorstr = "WRYOBPGD";
int t,n,tg,cnt,ans;
int stat[MAXN][MAXN];
pair<int,int> start[3];
bool valid(int x,int y) {
  return (x>=0&&x<n) && (y>=0&&y<n);
}
int main()
{
  IOS();
  cin>>t;
  while (t--) {
    cin>>n;
    ans = 0;
    MEM(stat,0);
    cnt = 0;
    REP (i,3) {
      string c;
      int x,y,j;
      cin>>c>>x>>y;
      if (c[0] == 'R') j=0;
      else if (c[0] == 'Y') j=1;
      else j=2;
      start[j] = {x,y};
    }
    string itg;
    cin>>itg;
    //debug(itg);
    tg = colormap[itg[0]];
    if (tg==7) {
      cout<<n*n<<endl;
      continue;
    }
    REP (dis,n) {
      if (dis%100==0)debug(dis);
      REP (i,3) {
        for (int x=-dis;x<=dis;x++) {
          int curX = start[i].X + x;
          int curY = start[i].Y + dis;
          if (!valid(curX,curY)) continue;
          if (stat[curX][curY] == tg) cnt--;
          stat[curX][curY] += (1<<i);
          if (stat[curX][curY]==tg) cnt++;
        }
        if (dis>0){
          for (int x=-dis;x<=dis;x++) {
            int curX = start[i].X + x;
            int curY = start[i].Y - dis;
            if (!valid(curX,curY)) continue;
            if (stat[curX][curY] == tg) cnt--;
            stat[curX][curY] += (1<<i);
            if (stat[curX][curY]==tg) cnt++;
          }
        }
          for (int x=-dis+1;x<dis;x++) {
            int curX = start[i].X + dis;
            int curY = start[i].Y + x;
            if (!valid(curX,curY)) continue;
            if (stat[curX][curY] == tg) cnt--;
            stat[curX][curY] += (1<<i);
            if (stat[curX][curY]==tg) cnt++;
          }
          for (int x=-dis+1;x<dis;x++) {
            int curX = start[i].X - dis;
            int curY = start[i].Y - x;
            if (!valid(curX,curY)) continue;
            if (stat[curX][curY] == tg) cnt--;
            stat[curX][curY] += (1<<i);
            if (stat[curX][curY]==tg) cnt++;
          }
      }
      ans = max(ans,cnt);

    }
    //debug(tg);


    cout<<ans<<endl;
  }
	return 0;
}
