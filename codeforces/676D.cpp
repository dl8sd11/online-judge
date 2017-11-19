#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/

#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define IN(A, B, C) assert( B <= A && A <= C)
#define MP make_pair
#define PB push_back
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007
#define X first
#define Y second
const double pi=acos(-1.0);
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef map<int,int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;

/****** Template of some basic operations *****/
template<typename T, typename U> inline void amin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void amax(T &x, U y) { if(x < y) x = y; }
/**********************************************/


/********** Main()  function **********/
int main()
{
	int n,m;
	cin>>n>>m; // y,x
	bool door[n][m][4][4]; //0上1右2下3左
	REP(i,n){
		REP(j,m){
			char tmp ;
			cin>>tmp;
			switch (tmp) {
				case '+':
					door[i][j][0][0]=1;
					door[i][j][0][1]=1;
					door[i][j][0][2]=1;
					door[i][j][0][3]=1;
					break;
				case '-':
					door[i][j][0][0]=0;
					door[i][j][0][1]=1;
					door[i][j][0][2]=0;
					door[i][j][0][3]=1;
					break;
				case '|':
					door[i][j][0][0]=1;
					door[i][j][0][1]=0;
					door[i][j][0][2]=1;
					door[i][j][0][3]=0;
					break;
				case '^':
					door[i][j][0][0]=1;
					door[i][j][0][1]=0;
					door[i][j][0][2]=0;
					door[i][j][0][3]=0;
					break;
				case '>':
					door[i][j][0][0]=0;
					door[i][j][0][1]=1;
					door[i][j][0][2]=0;
					door[i][j][0][3]=0;
					break;
				case 'v':
					door[i][j][0][0]=0;
					door[i][j][0][1]=0;
					door[i][j][0][2]=1;
					door[i][j][0][3]=0;
					break;
				case '<':
					door[i][j][0][0]=0;
					door[i][j][0][1]=0;
					door[i][j][0][2]=0;
					door[i][j][0][3]=1;
					break;
				case 'L':
					door[i][j][0][0]=1;
					door[i][j][0][1]=1;
					door[i][j][0][2]=1;
					door[i][j][0][3]=0;
					break;
				case 'R':
					door[i][j][0][0]=1;
					door[i][j][0][1]=0;
					door[i][j][0][2]=1;
					door[i][j][0][3]=1;
					break;
				case 'U':
					door[i][j][0][0]=0;
					door[i][j][0][1]=1;
					door[i][j][0][2]=1;
					door[i][j][0][3]=1;
					break;
				case 'D':
					door[i][j][0][0]=1;
					door[i][j][0][1]=1;
					door[i][j][0][2]=0;
					door[i][j][0][3]=1;
					break;
				case '*':
					door[i][j][0][0]=0;
					door[i][j][0][1]=0;
					door[i][j][0][2]=0;
					door[i][j][0][3]=0;
					break;
			} //door input
			REP(l,3){
				REP(k,4){
					door[i][j][l+1][k] = door[i][j][l][(k+5)%4];
				}
			}
		}
	}

	int xt,yt;
	int xm,ym;
	cin>>xt>>yt>>xm>>ym;

	queue<VI> bfs;
	VI init{xt-1,yt-1,0,0,0};
	bfs.push(init);
	bool found = false;
	while(bfs.size()){
		VI now = bfs.front();
		bfs.pop();
		int nowx= now[0];
		int nowy = now[1];
		int nowd = now[2];
		int nows = now[3];
		int nowl = now[4];
		REP(ti,5){
			cout<<now[ti]<<' ';
		}
		cout<<endl;
		if(nowx==xm-1 and nowy == ym-1){
			cout<<nows<<endl;
			found = true;
			break;
		}
		bool isopen = false;
		if(door[nowx][nowy][nowd][0]){
			if(nowx>0 and door[nowx-1][nowy][nowd][2]){
				bfs.push(VI{nowx-1,nowy,nowd,nows+1,0});  //還要隔壁有開
			isopen = true;}
		}
		if(door[nowx][nowy][nowd][1]){
			if(nowx<m-1 and door[nowx][nowy+1][nowd][3]){
				bfs.push(VI{nowx,nowy+1,nowd,nows+1,0});
			  isopen = true;
			}
		}
		if(door[nowx][nowy][nowd][2]){
			if(nowx<n-1 and door[nowx+1][nowy][nowd][0]){
				bfs.push(VI{nowx+1,nowy,nowd,nows+1,0});
			  isopen = true;
			}
		}
		if(door[nowx][nowy][nowd][3]){
			if(nowy>0 and door[nowx][nowy-1][nowd][1]){
				bfs.push(VI{nowx,nowy-1,nowd,nows+1,0});
			  isopen = true;
			}
		}
		if(!isopen){
		
			if(nowl==1){
				continue;
			}
			else{
				bfs.push(VI{nowx,nowy,(nowd+5)%4,nows+1,1});
				bfs.push(VI{nowx,nowy,(nowd+6)%4,nows+2,1});
				bfs.push(VI{nowx,nowy,(nowd+7)%4,nows+3,1});
				continue;
			}
		}

		bfs.push(VI{nowx,nowy,(nowd+5)%4,nows+1,0});

	}
	if(!found){
		cout<<-1<<endl;
	}




	return 0;
}
