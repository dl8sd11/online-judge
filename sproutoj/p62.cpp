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

int m[9][9];

bool solve(int idx) {
  //debug(idx);
  if (idx == 81) {
    debug("CONS");
    return true;
  }
  int x = idx % 9;
  int y = idx / 9;
  if (m[y][x]) return solve(idx+1);
  bool f[10] = {};
  int tm[9][9];
  REP (i,9) {
    REP (j,9) {
      tm[i][j] = m[i][j];
    }
  }
  REP (i,9) {
    f[m[y][i]] = 1;
    f[m[i][x]] = 1;
  }
  REP (i,3) {
    REP (j,3) {
      f[m[(y/3)*3+i][(x/3)*3+j]] = 1;
    }
  }

  bool ret = 0;
  REP1 (k,9) {
    if (!f[k]) m[y][x] = k;
    else continue;
    //debug(mp(idx,k));
    ret |= solve(idx+1);
    if (ret) break;
    REP (i,9) {
      REP (j,9) {
        m[i][j] = tm[i][j];
      }
    }
  }

  return ret;
}
int main()
{
  IOS();
  string a;
  while (1) {
    getline(cin,a);
    if (a == "end") {
      return 0;
    }
    MEM(m,0);
    REP (i,81) {
      if (a[i] != '.') m[i/9][i%9] = a[i]-'0';
    }
    bool flag = 0;
    REP (i,9) {
      bool f[10] = {};
      bool g[10] = {};
      REP (j,9) {
        if (m[i][j] != 0 && f[m[i][j]]) flag = 1;
        if (m[j][i] != 0 && g[m[j][i]]) flag = 1;
        f[m[i][j]] = 1;
        g[m[j][i]] = 1;
      }
    }

    REP (i,3) {
      REP (j,3) {
        bool f[10] = {};
        REP (k,3) {
          REP (l,3) {
            if (m[i*3+k][j*3+l] != 0 && f[m[i*3+k][j*3+l]]) flag = 1;
            f[m[i*3+k][j*3+l]] = 1;
          }
        }
      }
    }

    if (flag) {
      cout<<"No solution."<<endl;
      continue;
    }

    if (solve(0)) {
      REP (j,81) cout<<m[j/9][j%9];
      cout<<endl;
    } else {
      cout<<"No solution."<<endl;
    }
  }


	return 0;
}
