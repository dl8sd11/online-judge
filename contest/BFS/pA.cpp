#include <bits/stdc++.h>
using namespace std;
typedef int ll;
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


struct pos {
  int x,y,z;
}s,t;
int l,r,c;
char ch;
int m[40][40][40];
int dis[40][40][40];

int dx[] = {0,-1,0,1,0,0};
int dy[] = {0,0,-1,0,1,0};
int dz[] = {-1,0,0,0,0,1};

bool valid(pos cur) {
  if (cur.x < 0 || cur.x >= l) return false;
  if (cur.y < 0 || cur.y >= r) return false;
  if (cur.z < 0 || cur.x >= c) return false;
  return true;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    while (cin >> l >> r >> c) {
      if (l == 0 && r == 0 && c == 0 ) {
	break;
      }
      MEM(m,0);
      REP (i,l) {
	REP (j,r) {
	  REP (k,c) {
	    cin >> ch;
	    if (ch == 'S') {
	      s = (pos){i,j,k};
	    } else if (ch == 'E') {
	      t = (pos){i,j,k};
	    } else if (ch == '#') {
	      m[i][j][k] = 1;
	    }
	  }
	}
      }

      MEM(dis,-1);
      queue<pos> q;
      q.push(s);

      dis[s.x][s.y][s.z] = 0;
      while (q.size()){
	pos cur = q.front();q.pop();
	REP (i,6) {
	  pos tmp = cur;
	  tmp.x += dx[i];
	  tmp.y += dy[i];
	  tmp.z += dz[i];
	  if (valid(tmp) && m[tmp.x][tmp.y][tmp.z] != 1 && dis[tmp.x][tmp.y][tmp.z] == -1) {
	    dis[tmp.x][tmp.y][tmp.z] = dis[cur.x][cur.y][cur.z] + 1;
	    q.push(tmp);
	  }
	}
      }

      if (dis[t.x][t.y][t.z] == -1) {
	cout << "Trapped!" << endl;
      } else {
	cout << "Escaped in " << dis[t.x][t.y][t.z] << " minute(s)." << endl;
      }

      
    }
    return 0;
}
