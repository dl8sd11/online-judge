#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<sstream>
#include<cmath>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
typedef double lf;
typedef pair<ll,ll> ii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define FILL(i,n) memset(i,n,sizeof i)
#define X first
#define Y second
#define SZ(_a) (int)_a.size()
#define ALL(_a) _a.begin(),_a.end()
#define pb push_back
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
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif // brian
//}


const ll MAXn=1e5+5,MAXlg=__lg(MAXn)+2;
const ll MOD=1000000007;
const ll INF=ll(1e15);

int n,len;
int a[1000][1000] = {};
vector<int> q;
int main()
{
    IOS();
    cin>>n;
    for(ll i=n;i>=2;i--){
      for(ll j=0;j<SZ(q);j++){
        cout<<q[j]%10<<"_";
      }
      for(ll j=0;j<(i-1)*4+1;j++)cout<<i%10;
      for(ll j=SZ(q)-1;j>=0;j--){
        cout<<"_"<<q[j]%10;
      }
      q.push_back(i);
      cout<<"\n";

      for(ll j=0;j<SZ(q);j++){
        cout<<q[j]%10<<"_";
      }
      for(ll j=0;j<(i-2)*4+1;j++)cout<<"_";
      for(ll j=SZ(q)-1;j>=0;j--){
        cout<<"_"<<q[j]%10;
      }

      cout<<"\n";
    }

    for(ll i=0;i<SZ(q);i++)cout<<q[i]%10<<"_";
    cout<<1;
    for(ll i=SZ(q)-1;i>=0;i--)cout<<"_"<<q[i]%10;
    cout<<"\n";


    for(ll i=2;i<=n;i++){

      for(ll j=0;j<SZ(q);j++){
        cout<<q[j]%10<<"_";
      }
      for(ll j=0;j<(i-2)*4+1;j++)cout<<"_";
      for(ll j=SZ(q)-1;j>=0;j--){
        cout<<"_"<<q[j]%10;
      }
      q.pop_back();
      cout<<"\n";
      for(ll j=0;j<SZ(q);j++){
        cout<<q[j]%10<<"_";
      }
      for(ll j=0;j<(i-1)*4+1;j++)cout<<i%10;
      for(ll j=SZ(q)-1;j>=0;j--){
        cout<<"_"<<q[j]%10;
      }

      cout<<"\n";
    }
}
