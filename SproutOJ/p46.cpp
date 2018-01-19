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
int foodx[] = {-1,-1,-1,0,0,0,1,1,1};
int foody[] = {-1,0,1,-1,0,1,-1,0,1};
int t,n,tg;
int stat[MAXN][MAXN];
int visit[3][MAXN][MAXN];
int cnt;
int ans = 0;

struct Node {
  Node *prev, *next;
  pair<int,int> data;
  Node (pair<int,int> id) : data(id){}
};
class QUEUE{
public:
  Node *head, *tail;
  QUEUE(){
    head=tail=0;
  }
  void push(pair<int,int> in) {
    Node *tmp = new Node(in);
    if (head == NULL) {
      head = tmp;
      tail = tmp;
      head->prev = NULL;
      head->next = NULL;
    } else {
      tmp->prev = tail;
      tmp->next = NULL;
      tail->next = tmp;
      tail = tmp;
    }
  }
  pair<int,int> front() {
    //debug(head->data);
    return head->data;
  }
  void pop() {
    if (head == tail) {
      head = tail = NULL;
    } else {
      Node *d = head;
      head = head->next;
      delete d;
    }
  }
  int size() {
    if (head) return 1;
    else return 0;
  }
};
QUEUE paint[3];
int main()
{
  IOS();
  cin>>t;
  while (t--) {
    cin>>n;
    ans = 0;
    MEM(stat,0);
    MEM(visit,0);
    cnt = 0;
    REP (j,3) {
      REP (i,n+2) {
        visit[j][0][i] = 1;
        visit[j][i][n+1] = 1;
        visit[j][i][0] = 1;
        visit[j][n+1][i] = 1;
      }
    }
    REP (i,3) {
      string c;
      int x,y,j;
      cin>>c>>x>>y;
      if (c[0] == 'R') j=0;
      else if (c[0] == 'Y') j=1;
      else j=2;
      visit[j][x+1][y+1] = 1;
      paint[j].push(mp(x+1,y+1));
      paint[j].push(mp(-1,-1));
    }
    string itg;
    cin>>itg;
    //debug(itg);
    tg = colormap[itg[0]];
    if (tg==7) {
      cout<<n*n<<endl;
      continue;
    }
    //debug(tg);
    while (paint[0].size()||paint[1].size()||paint[2].size()) {
      //debug(ans);
      REP (i,3) {
        while (paint[i].size()) {
          int curX = paint[i].front().X;
          int curY = paint[i].front().Y;
          paint[i].pop();
          if (curX == -1) {
            paint[i].push(mp(-1,-1));
            if (paint[i].front().X == -1) {
              paint[i].pop();
            }
            break;
          }
          if (stat[curX][curY]==tg)cnt--;
          stat[curX][curY]+=(1<<i);
          if (stat[curX][curY]==tg)cnt++;
          int dx;
          int dy;
          REP (j,9) {
            dx = curX + foodx[j];
            dy = curY + foody[j];
            if (!visit[i][dx][dy]) {
              paint[i].push(mp(dx,dy));
              visit[i][dx][dy] = 1;
            }
          }
        }
      }
      ans = max(ans,cnt);
      //debug(ans);
    }
    cout<<ans<<endl;
  }
	return 0;
}
