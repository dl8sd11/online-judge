#include <bits/stdc++.h>
using namespace std;

#define MAXN 100
#define INF INT_MAX
int n;
int g[MAXN][MAXN],lx[MAXN],ly[MAXN],slack_y[MAXN];
int match_y[MAXN];//要保證g是完全二分圖  
bool vx[MAXN],vy[MAXN];
bool dfs(int x,bool adjust=1){//DFS找增廣路，is=1表示要擴充
	if(vx[x])return 0;
	vx[x]=1;
	for(int y=0;y<n;++y){
		if(vy[y])continue;
		int t=lx[x]+ly[y]-g[x][y];
		if(t==0){
			vy[y]=1;
			if(match_y[y]==-1||dfs(match_y[y],adjust)){
				if(adjust)match_y[y]=x;
				return 1;
			}
		}else if(slack_y[y]>t)slack_y[y]=t;
	}
	return 0;
}
inline int km(){
	memset(match_y,-1,sizeof(int)*n);
	memset(ly,0,sizeof(int)*n);
	for(int x=0;x<n;++x){
		lx[x]=-INF;
		for(int y=0;y<n;++y){
			lx[x]=max(lx[x],g[x][y]);
		}
	}
	for(int x=0;x<n;++x){
		for(int y=0;y<n;++y)slack_y[y]=INF;
		memset(vx,0,sizeof(bool)*n);
		memset(vy,0,sizeof(bool)*n);
		if(dfs(x))continue;
		bool flag=1;
		while(flag){
			int cut=INF;
			for(int y=0;y<n;++y){
				if(!vy[y]&&cut>slack_y[y])cut=slack_y[y];
			}
			for(int j=0;j<n;++j){
				if(vx[j])lx[j]-=cut;
				if(vy[j])ly[j]+=cut;
				else slack_y[j]-=cut;
			}
			for(int y=0;y<n;++y){
				if(!vy[y]&&slack_y[y]==0){
					vy[y]=1;
					if(match_y[y]==-1||dfs(match_y[y],0)){
						flag=0;//測試成功，有增廣路 
						break;
					}
				}
			}
		}
		memset(vx,0,sizeof(bool)*n);
		memset(vy,0,sizeof(bool)*n);
		dfs(x);//最後要記得擴充增廣路
	}
	int ans=0;
	for(int y=0;y<n;++y)if(g[match_y[y]][y]!=-INF)ans+=g[match_y[y]][y];
	return ans;
}


#define REP(i,n) for(int i=0;i<n;i++)
#define SQ(i) (i)*(i)

int x[2][MAXN],y[2][MAXN];
int main()
{
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    cin >> n;
    REP (j,2) {
        REP (i,n) {
            cin >> x[j][i];
            cin >> y[j][i];
        }
    }

    REP (i,n) {
        REP (j,n) {
            g[i][j] = -SQ(x[0][i]-x[1][j]) - SQ(y[0][i]-y[1][j]);
        }
    }

    

    cout << "Yes" << endl;
	int ans = km();
	int tst = 0;
	REP (i,n) {
		tst += g[match_y[i]][i];
		cout << match_y[i] + 1 << " " << i + 1 << endl;
	}
	// assert(ans == tst);
	cout << ans << endl;
    return 0;
}