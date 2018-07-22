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
typedef pair<double, double> pdd;
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
const ll MAXN = 503;
int n;
pdd p[MAXN];
pdd ans;
double r;
/********** Main()  function **********/
double pf(double x){return x*x;}
pdd center(pdd a,pdd b,pdd c){
    debug(a,b,c);
    double A1 = (b.X - a.X) * 2,B1 = (b.Y - a.Y) * 2,C1 = pf(b.X) + pf(b.Y) - pf(a.X) - pf(a.Y);
    double A2 = (c.X - b.X) * 2,B2 = (c.Y - b.Y) * 2,C2 = pf(c.X) + pf(c.Y) - pf(b.X) - pf(b.Y);
    assert((A1 * B2 - A2 * B1)!=0);
    if((A1 * B2 - A2 * B1)==0)return pdd{(a.X+c.X)/2,(a.Y+c.Y)/2};
    return (pdd){(C1 * B2 - C2 * B1) / (A1 * B2 - A2 * B1),(A1 * C2 - A2 * C1) / (A1 * B2 - A2 * B1)};
}

double dis(pdd a,pdd b){
  return sqrt((a.X-b.X)*(a.X-b.X)+(a.Y-b.Y)*(a.Y-b.Y));
}
int main()
{
  IOS();
  srand(time(0));
  while(cin>>n&&n!=0){
    REP(i,n)cin>>p[i].X>>p[i].Y;
    random_shuffle(p,p+n);
    pary(p,p+n);
    ans = p[0];
    r = 0;
    for(int i=0;i<n;i++){
      if(dis(ans,p[i]) > r){
        ans = p[i];
        r = 0;
        for(int j=0;j<i;j++){
          if(dis(ans,p[j])>r){
            ans.X = (p[i].X + p[j].X)/2;
            ans.Y = (p[i].Y + p[j].Y)/2;
            r = dis(p[i],ans);
            for(int k=0;k<j;k++){
              debug(p[k]);
              if(dis(ans,p[k]) > r){
                ans = center(p[i],p[j],p[k]);
                r = dis(p[k],ans);
              }
            }
          }
        }
      }
    }
    cout<<fixed<<setprecision(2)<<ans.X<<" "<<ans.Y<<" "<<r<<endl;
  }
	return 0;
}
