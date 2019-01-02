#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double lf;
typedef pair<ll,ll> ii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define RST(i,n) memset(i,n,sizeof i)
#define SZ(a) (int)a.size()
#define ALL(a) a.begin(),a.end()
#define X first
#define Y second
#define mkp make_pair
#define pb push_back
#define eb emplace_back
#define pob pop_back
#ifdef tmd
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<", ";_do(_t...);}
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
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif // cold66
//}
template<class T> inline bool chkmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool chkmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MAXn=205,MAXlg=__lg(MAXn)+2;
const ll MOD=1000000007;
const ll INF=0x3f3f3f3f;

ii d[MAXn];
ll cnt[MAXn][MAXn];
vector<ll> xx,yy;

ll query(ll x,ll y,ll u,ll v){
  return cnt[u][v] - cnt[u][y-1] - cnt[x-1][v] + cnt[x-1][y-1];
}

int main(){
  IOS();
  ll t;
  cin >> t;
  while(t--){
    xx.clear();
    yy.clear();
    RST(cnt,0);

    ll k,n;
    bool fg = false;
    cin >> k >> n;
    REP(i,MAXn) d[i] = mkp(n,n);
    REP(i,k){
      cin >> d[i].X >> d[i].Y;
      xx.eb(d[i].X);
      yy.eb(d[i].Y);
      if(d[i].X == 0 && d[i].Y == n-1) fg = true;
      if(d[i].X == n-1 && d[i].Y == 0) fg = true;
      if(d[i].X == 0 && d[i].Y == 0) fg = true;
      if(d[i].X == n-1 && d[i].Y == n-1) fg = true;
    }
    REP(i,k){
      for(ll j=i+1;j<k;j++){
        if(d[i].X == 0 && d[j].X == n-1) fg = true;
        if(d[i].X == n-1 && d[j].X == 0) fg = true;
        if(d[i].Y == 0 && d[j].Y == n-1) fg = true;
        if(d[i].Y == n-1 && d[j].Y == 0) fg = true;
      }
      if(fg) break;
    }
    if(!fg && k < 4){
      cout << "no" << endl;
      continue;
    }
    if(fg){
      cout << "yes" << endl;
      continue;
    }
    sort(ALL(xx));
    sort(ALL(yy));
    xx.resize(unique(ALL(xx))-xx.begin());
    yy.resize(unique(ALL(yy))-yy.begin());
    REP(i,k){
      d[i].X = ll(lower_bound(ALL(xx),d[i].X)-xx.begin()+1);
      d[i].Y = ll(lower_bound(ALL(yy),d[i].Y)-yy.begin()+1);
    }
    
    REP(i,k) cnt[d[i].X][d[i].Y]++;
    REP1 (i,MAXn-1) {
        REP1 (j,MAXn-1) {
            cnt[i][j] += cnt[i-1][j] + cnt[i][j-1] - cnt[i-1][j-1];
        }
    }
    
    REP(i,k){
      for(ll j=i+1;j<k;j++){
        if ((d[i].X >= d[j].X && d[i].Y >= d[i].Y )|| (d[i].X <= d[j].X && d[i].Y <= d[i].Y )) {
            ll ix = min(d[i].X,d[j].X);
            ll iy = min(d[i].Y,d[j].Y);
            ll jx = max(d[i].X,d[j].X);
            ll jy = max(d[i].Y,d[j].Y);
            ll a = query(1,iy,jx,MAXn-1) - 2;
            ll b = query(ix,1,MAXn-1,jy) - 2;
            ll ab = query(ix,iy,jx,jy) - 2;
            if((a >= 1 && b >= 1) && ab == 0){
                fg = true;
            }
            if((a >= 2 || b >= 2) && ab >= 1){
                fg = true;
            }
        } else {
            ll ix = min(d[i].X,d[j].X);
            ll iy = min(d[i].Y,d[j].Y);
            ll jx = max(d[i].X,d[j].X);
            ll jy = max(d[i].Y,d[j].Y);
            ll a = query(ix,iy,MAXn-1,MAXn-1) - 2;
            ll b = query(1,1,jx,jy) - 2;
            ll ab = query(ix,iy,jx,jy) - 2;
            if((a >= 1 && b >= 1) && ab == 0){
                fg = true;
            }
            if((a >= 2 || b >= 2) && ab >= 1){
                fg = true;
            }
        }
      }
      if(fg) break;
    }
    if(fg) cout << "yes" << endl;
    else cout << "no" << endl;
  }
}
