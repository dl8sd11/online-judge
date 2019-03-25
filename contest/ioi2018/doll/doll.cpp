#include <bits/stdc++.h>
#include "doll.h"
using namespace std;
typedef long long ll;
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
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
// const ll MAXN = 

int S;

bool state[2000001];

void fll(int id,int val,vector<int> &X,vector<int> &Y) {
  state[id] = !state[id];
  if (!state[id]) {
    if (X[id-1] == 1) {
      X[id-1] = val;
    } else {
      fll(-X[id-1],val,X,Y);
    }
  } else {
    if (Y[id-1] == 1) {
      Y[id-1] = val;
    } else {
      fll(-Y[id-1],val,X,Y);
    }
  }
}
void build(int id,bool st,int sz,vector<int> &X,vector<int> &Y,vector<int> &C) {
  debug(sz,id);
  if (sz == 1) {
    if (st) {
      X[id-1] = 1;
    } else {
      Y[id-1] = 1;
    }
    return;
  } 
  S++;
  X.eb(INF);
  Y.eb(INF);
  if (id > 0) {
    if (st) {
      X[id-1] = -S;
    } else {
      Y[id-1] = -S;
    }
  } else {
    C[-id] = -S;
  }

  if (sz == 2) {
    X[S-1] = 1;
    Y[S-1] = 1;
  } else {
    int ts = S;
    build(ts,true,sz-sz/2,X,Y,C);
    build(ts,false,sz/2,X,Y,C);
  }
}
void create_circuit(int M, std::vector<int> A) {
  int N = A.size();
  std::vector<int> C(M + 1);
  std::vector<int> X;
  std::vector<int> Y;

  vector<vector<int>> edg(M+1);

  int lst = 0;
  for (auto e : A) {
    edg[lst].emplace_back(e);
    lst = e;
  }
  edg[lst].emplace_back(0);
  debug(edg);

  REP (i,M+1) {
    bool fs = true;
    if (SZ(edg[i]) == 1) {
      C[i] = edg[i].front();
    } else{
      int hd = S+1;

      build(-i,true,SZ(edg[i]),X,Y,C);
      debug(X);
      debug(Y);
      for (ll j=hd;j<=S;j++) {
        state[j] = true;
      }
      for (auto v : edg[i]) {
        debug(v,hd);
        fll(hd,v,X,Y);
      }
    }
  }
  debug(C);
  debug(X);
  debug(Y);
  answer(C, X, Y);
}
