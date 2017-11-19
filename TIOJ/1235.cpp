//{
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double lf;
typedef pair<ll,ll> ii;
typedef std::vector<pair<int,int> > vi;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define FILL(i,n) memset(i,n,sizeof i)
#define X first
#define Y second
#define SZ(_a) (int)_a.size()
#define ALL(_a) _a.begin(),_a.end()
#define pb push_back
#define mp make_pair
#ifdef brian
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


const ll MAXn=5e5+5,MAXlg=__lg(MAXn)+2;
const ll MOD=1000000007;
const ll INF=ll(1e15);

//R、O、Y、G、B、I、P、L、W
vector<int> g[9][9];
map<char, int> mapchar;
int garden[9][9];
char mapint[10] ={'*','R','O','Y','G','B','I','P','L','W'};
vector<pair<int,int> > un;
vector<int> out[9];

void eraseG(int x,int y,int j){
  REP(b,9){
    if(garden[x][b]==0){
      std::vector<int>::iterator it;
      it = find(g[x][b].begin(),g[x][b].end(),g[x][y].at(j));

      if(it!=g[x][b].end()){

        g[x][b].erase(it);
      }

    }


    if(garden[b][y]==0){
      std::vector<int>::iterator it;
      it = find(g[b][y].begin(),g[b][y].end(),g[x][y].at(j));
      if(it!=g[b][y].end()){

        g[b][y].erase(it);
      }
    }
  }
  int py = int(x/3)*3;
  int px = int(y/3)*3;

  REP(k,3){
    REP(l,3){
      if(garden[k+py][l+px]==0){
        std::vector<int>::iterator it;
        it = find(g[k+py][l+px].begin(),g[k+py][l+px].end(),g[x][y].at(j));
        if(it!=g[k+py][l+px].end()){

          g[k+py][l+px].erase(it);
        }
      }

    }
  }
}
bool cmp(const pair<int,int>& a,const pair<int,int>& b){
  return g[a.X][a.Y].size()<g[b.X][b.Y].size(); //something worng
}
bool plantGarden(int unidx){

  if(unidx>int(un.size()-1))return true;
  int x = un[unidx].X;
  int y = un[unidx].Y;
  int vs = int(g[x][y].size());
  if (vs==0) return false;

  for(int j=0;j<vs;j++){ //guess a num
    vector<int> tg[9][9];
    int tgarden[9][9];


    garden[x][y] = g[x][y].at(j);

    REP(a,9){
      REP(b,9){
        tg[a][b] = g[a][b];
        tgarden[a][b] = garden[a][b];
      }
    }

    eraseG(x,y,j);

    if(plantGarden(unidx+1)){

      return true;
    }
    else{
      REP(a,9){
        REP(b,9){
          g[a][b] = tg[a][b];
          garden[a][b] = tgarden[a][b];
        }
      }
    }
  }
  return false;
}

void initMap(){
  mapchar['*'] = 0;
  mapchar['R'] = 1;
  mapchar['O'] = 2;
  mapchar['Y'] = 3;
  mapchar['G'] = 4;
  mapchar['B'] = 5;
  mapchar['I'] = 6;
  mapchar['P'] = 7;
  mapchar['L'] = 8;
  mapchar['W'] = 9;
}
int main(){
  IOS();
  initMap();
  REP(i,9){
    REP(j,9){
      char tmp;
      cin>>tmp;
      if(tmp=='*'){
        out[i].pb(int(j));
      }
      garden[i][j] = mapchar[tmp];
    }
  }


  REP(i,9){
    REP(j,9){
      if(garden[i][j]==0){
        bool o[10] ={};
        REP(k,9){

          o[garden[i][k]] = true;
          o[garden[k][j]] = true;
        }
        int py = int(i/3)*3;
        int px = int(j/3)*3;

        REP(k,3){
          REP(l,3){
            o[garden[py+k][px+l]] = true;
          }
        }

        REP(k,9){
          if(o[k+1]==false)g[i][j].pb(int(k+1));
        }
        if(g[i][j].size()>1)un.pb(mp(i,j));
        if(g[i][j].size()==1){
          garden[i][j] = g[i][j].at(0);
          eraseG(i,j,0);

        }
      }
      else{
        g[i][j].pb(garden[i][j]);
      }
    }
  }

  int cnt =0;
  for(int i=0;i<int(un.size());i++){
      if(g[un[i].X][un[i].Y].size()==1){
        garden[un[i].X][un[i].Y] = g[un[i].X][un[i].Y].at(0);
        eraseG(un[i].X,un[i].Y,0);
        un.erase(un.begin()+i);
        cnt++;
      }
  }
  while(cnt){
    cnt=0;
    for(int i=0;i<int(un.size());i++){
        if(g[un[i].X][un[i].Y].size()==1){
          garden[un[i].X][un[i].Y] = g[un[i].X][un[i].Y].at(0);
          eraseG(un[i].X,un[i].Y,0);
          un.erase(un.begin()+i);
          cnt++;
        }
    }
  }
  if(plantGarden(0)){
    REP(i,9){
      int sz = int(out[i].size());
      if(sz==0)cout<<endl;
      else{
        REP(j,sz){
          cout<<mapint[(garden[i][out[i][j]])];
        }
        cout<<endl;
      }
    }
  }
  else{
    cout<<"Too Bad Ans 404"<<endl;
  }


}
