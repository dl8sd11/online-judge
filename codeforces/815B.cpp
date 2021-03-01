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
typedef vector<long long int> VI;
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
VI u;
int64 x,y,l,r;
void pbu(uint64 in) {
	if(in>=l&&in<=r)
		u.PB(in);
	return;
}

void solve(){
	int xb = 0;
	int yb = 0;

	float log_r = log(r);
	xb= log_r/log(x);
	yb= log_r/log(y);

	uint64 a = 0;
	uint64 xt = 1;
	uint64 yt = 1;

	REP(i,xb+1){
		if(i!=0)
			xt *= x;
		yt = 1;
		REP(j,yb+1){
			if(j!=0)
			 	yt *= y;
			 if(yt+xt>r){
				 break;
			 }
			 else{
				 pbu(xt+yt);
			 }
		}
	}
	int64 ans = 0;

	sort(all(u));
	uint64 u_size = u.size();
	if(!u.size()){
		cout<<r-l+1<<endl;
		return;
	}

	int64	prevU = u.at(0);
	// cout<<"DEBUG"<<prevU<<endl;
	ans = max(ans,prevU - l);
	for(int64 i=1;i<u_size;i++){
		ans = max(u.at(i)-prevU-1,ans);
		prevU = u.at(i);
		// cout<<"DEBUG"<<prevU<<endl;
	}

	ans = max(ans, r - prevU);
	cout<<ans<<endl;
	return;
}
/********** Main()  function **********/
int main()
{
	cin>>x>>y>>l>>r;
	solve();
	return 0;
}
