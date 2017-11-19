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
	cin>>n>>m;
	bool o[m][n];
	int t=n,b=-1,l=m,r=-1;
	REP(i,n){
		REP(j,m){
			char tmp;
			cin>>tmp;
			if(tmp=='W')
				o[j][i] = 0;
			else{
				o[j][i] = 1;
				if(j<l)
					l=j;
				if(j>r)
					r=j;
				if(i>b)
					b=i;
				if(i<t)
					t=i;
			}
		}
	}
	if(t==n){
		cout<<'1'<<endl;
		return 0;
	}
	int w = r-l+1;
	int h = b-t+1;

	int s = max(w,h);
	if(s>n||s>m){
		cout<<"-1"<<endl;
		return 0;
	}

	int sum =0;

	FOR(j,t,b+1,1){
		FOR(i,l,r+1,1){
			sum+=1-o[i][j];
		}
	}
	cout<<sum+(s-min(w,h))*s<<endl;



	return 0;
}
