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

ll strtoint(string num){
  if(SZ(num)>1&&num[SZ(num)-1]=='0')return -1;
  ll ret = 0;
  ll ten = 1;
  if(SZ(num)==0)return -1;
  REP(i,SZ(num)){
    if(num[i]>'9'||num[i]<'0')return -1;
    else ret += (num[i] - '0')*ten;
    ten *= 10;
  }
  if(ret > 255)return -1;
  return ret;
}
ll iptol(string ip){
  ll ret = 0,rate = 1;
  string tmp;
  for(ll i=SZ(ip)-1;i>=0;i--){
    if(ip[i]=='.'){
      ll res = strtoint(tmp);
      if(res == -1) return -1;
      ret += res*rate;
      tmp = string();
      rate *= 256;
    } else {
      tmp += ip[i];
    }
  }

  ll res = strtoint(tmp);
  if(res == -1) return -1;
  ret += res * rate;
  return ret;
}
int main()
{
    IOS();
    string input;
    cin>>input;
    ll a = iptol(input);
    if(a==-1){
      cout<<"N"<<endl;
      return 0;
    }

    if(a >= iptol("1.0.0.0") && a <= iptol("126.255.255.255")){
      cout<<"A"<<endl;

    } else if(a>= iptol("128.0.0.0") && a <= iptol("191.255.255.255")){
      cout<<"B"<<endl;

    } else if(a >= iptol("192.0.0.0") && a <= iptol("223.255.255.255")){
      cout<<"C"<<endl;

    } else if(a >= iptol("224.0.0.0") && a <= iptol("239.255.255.255")){
      cout<<"D"<<endl;

    } else if(a >= iptol("240.0.0.0") && a <= iptol("247.255.255.255")){
      cout<<"E"<<endl;

    } else {
      cout<<"X"<<endl;
    }

}
