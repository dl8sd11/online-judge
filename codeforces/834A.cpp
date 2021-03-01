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
	int a,b;
	char tmp;
	cin>>tmp;
	if (tmp=='v'){
		a=0;
	}
	else if(tmp=='<'){
		a=1;
	}
	else if(tmp=='^'){
		a=2;
	}
	else{
		a=3;
	}
	cin>>tmp;
	if (tmp=='v'){
		b=0;
	}
	else if(tmp=='<'){
		b=1;
	}
	else if(tmp=='^'){
		b=2;
	}
	else{ //>
		b=3;
	}

	int64 n;
	cin>>n;

	int cw = a;
	int ccw = a;

	n%=4;
	REP(i,n){
		cw++;
		ccw--;
		if(cw==4)
			cw=0;
		if(ccw==-1)
			ccw=3;
	}
	if(cw==ccw){
		cout<<"undefined"<<endl;
	}
	else if(b==cw){
		cout<<"cw"<<endl;
	}
	else if(b==ccw){
		cout<<"ccw"<<endl;
	}
	else{
		cout<<"undefined"<<endl;
	}
	return 0;
}
