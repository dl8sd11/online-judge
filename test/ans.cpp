#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair <int , int> pii;

const int N = 1e5+10 , mod = 1e9+7 , L = 18 , M = 2e4+10 , Sq = 200;

vector <pii> g[N];
int par[N][L] , h[N] , ans[N] , fen[N] , s[Sq];
vector < pair <pii , int> > q[N];

void pre_dfs(int v , int p){
   h[v] = h[p] + 1;
   par[v][0] = p;
   for(int i = 1 ; i < L ; i++)
      par[v][i] = par[par[v][i - 1]][i - 1];
   for(auto x : g[v]){
      int u = x.first , w = x.second;
      if(u != p){
         pre_dfs(u , v);
      }
   }
}

int pr(int v , int x){
   for(int i = 0 ; i < L ; i++)
      if((1 << i) & x)
         v = par[v][i];
   return v;
}

int lca(int u , int v){
   if(h[u] > h[v])
      swap(u , v);
   v = pr(v , h[v] - h[u]);
   if(v == u)
      return v;
   for(int i = L - 1 ; i >= 0 ; i--)
      if(par[v][i] != par[u][i])
         v = par[v][i] , u = par[u][i];
   return par[v][0];
}

void add(int x , int mul){
   if(!x)
      return;
   for(int i = 1 ; i < Sq ; i++)
      s[i] += mul * x / i;
   for( ; x < M ; x += x & -x)
      fen[x] += mul;
}

int get(int x){
   int ret = 0;
   for( ; x ; x -= x & -x)
      ret += fen[x];
   return ret;
}

void dfs(int v , int p){
   for(auto x : g[v]){
      int u = x.first , w = x.second;
      if(u != p){
         add(w , 1);
         dfs(u , v);
         add(w , -1);
      }
   }
   for(auto x : q[v]){
      int t = x.first.first , mul = x.first.second , id = x.second;
      if(t < Sq)
         ans[id] += mul * s[t];
      else{
         int nw = 0;
         for(int i = 1 ; (i - 1) * t < M ; i++){
            int a = get(min(i * t - 1 , M - 1));
            a -= nw;
            ans[id] += a * (i - 1) * mul;
            nw += a;
         }
      }
   }
   //cout << v << " " << ans[0] << endl;
}

int32_t main(){
   ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   int n , m;
   cin >> n >> m;
   for(int i = 0 ; i < n - 1 ; i++){
      int u , v , w;
      cin >> u >> v >> w;
      u--; v--; w--;
      g[u].push_back({v , w});
      g[v].push_back({u , w});
   }
   pre_dfs(0 , 0);
   for(int i = 0 ; i < m ; i++){
      int u , v , t;
      cin >> u >> v >> t;
      u--; v--;
      int p = lca(u , v);
      q[p].push_back({{t , -2} , i});
      q[u].push_back({{t , 1} , i});
      q[v].push_back({{t , 1} , i});
      ans[i] = h[u] + h[v] - 2 * h[p] + 1;
   }
   dfs(0 , 0);
   for(int i = 0 ; i < m ; i++)
      cout << ans[i] << "\n";
   return 0;
}