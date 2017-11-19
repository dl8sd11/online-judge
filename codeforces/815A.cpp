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
int g[100][100];
int n,m;
VI col;
VI row;

void printG (){
	REP(j,n){
		REP(i,m)
			cout<<g[i][j]<<" ";
		cout<<endl;
	}
}
int scanVer(){
	REP(i,m){
			bool flag = false;
			REP(j,n){
				if(g[i][j]==0){
					flag = true;
					break;
				}
			}
			if(!flag){
				return i;
			}
	}
	return -1;
}

int scanHor(){
	REP(i,n){
			bool flag = false;
			REP(j,m){
				if(g[j][i]==0){
					flag = true;
					break;
				}
			}
			if(!flag){
				return i;
			}
	}
	return -1;
}

void printCR(){
	int col_size = col.size();
	int row_size = row.size();
	cout<<col_size+row_size<<endl;
	for(int i=0;i<col_size;i++){
		cout<<"col "<<col.at(i)<<endl;
	}
	for(int i=0;i<row_size;i++){
		cout<<"row "<<row.at(i)<<endl;
	}
}
void ans(){
		if(n>m){
			int res = scanVer();
			while(res != -1){
				col.PB(res+1);
				REP(i,n){
					g[res][i]--;
				}
				res = scanVer();
			}

			res = scanHor();
			while(res != -1){
				row.PB(res+1);
				REP(i,m){
					g[i][res]--;
				}
				res = scanHor();
			}

			int flag = true;
			REP(i,n){
				REP(j,m){
					if(g[j][i]!=0){
						flag = false;
						break;
					}
				}
			}
			if(flag)
				printCR();
			else
				cout<<"-1"<<endl;

		}
		else{

			int res = scanHor();
			while(res != -1){
				row.PB(res+1);
				REP(i,m){
					g[i][res]--;
				}
				res = scanHor();
			}

			res = scanVer();
			while(res != -1){
				col.PB(res+1);
				REP(i,n){
					g[res][i]--;
				}
				res = scanVer();
			}

			res = scanHor();
			while(res != -1){
				row.PB(res+1);
				REP(i,m){
					g[i][res]--;
				}
				res = scanHor();
			}

			int flag = true;
			REP(i,n){
				REP(j,m){
					if(g[j][i]!=0){
						flag = false;
						break;
					}
				}
			}
			if(flag)
				printCR();
			else
				cout<<"-1"<<endl;
		}

}
/********** Main()  function **********/
int main()
{

	cin>>n>>m;

	REP(i,n)
		REP(j,m)
			cin>>g[j][i];
	ans();
	return 0;
}
