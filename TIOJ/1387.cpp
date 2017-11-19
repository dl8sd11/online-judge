#include <bits/stdc++.h>
#include <vector>
#define REP(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define X first
#define Y second
using namespace std;
int n;
int vSize;
vector<pair<int,int> > stone;

int main(){
  cin>>n;
  
  REP(i,n){
   int w,v,c;
   cin>>w>>v>>c;
   REP(j,c){
     stone.pb(make_pair(w,v));
   }
  }
  sort(stone.begin(),stone.end());
  vSize = stone.size();
  int t;
  cin>>t;
  int dp[t][n];
  memset(dp,0,sizeof(dp));
  bool roll = false;
  for(int i=0;i<vSize;i++){
  	for(int j=0;j<t;j++){
			int ret = 0;
			
		}			
	}
} 
