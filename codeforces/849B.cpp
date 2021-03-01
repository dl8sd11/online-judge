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
int n;
int y[1003];
bool m[1003];
void IOS (){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
}

bool solve(int a,int b){
	MEM(m,0);
	int dx = b-a;
	int dy = y[b]-y[a];
	int gcd = __gcd(dx,dy);
	dx/=gcd;
	dy/=gcd;


	m[a]=1;
	m[b]=1;

	REP(i,n){
		if(!m[i]){

			int tdx = i-a;
			int tdy = y[i]-y[a];
			if(tdx<0){
				tdx*=-1;
				tdy*=-1;
			}
			int gcd = __gcd(tdx,tdy);

			tdx/=gcd;
			tdy/=gcd;


			if(dx==tdx&&dy==tdy)m[i]=1;
		}
	}



	bool flag = 0;
	int first = -1;
	REP(i,n){
		if(!m[i]){
			if(first==-1){
				first = i;
			} 
			else{
				int tdx = i-first;
				int tdy = y[i]-y[first];

				int gcd = __gcd(tdx,tdy);
				tdx/=gcd;
				tdy/=gcd;
				if(tdx!=dx or tdy!=dy)flag = true;
			}
		}
	}

	if(first==-1)return false;
	if(flag)return false;


	return true;
}

/********** Main()  function **********/
int main()
{

	IOS();
	cin>>n;
	REP(i,n)
		cin>>y[i];

	bool ans = false;
	ans|=solve(0,1);

	ans|=solve(0,2);

	ans|=solve(1,2);


	if(ans)cout<<"Yes"<<endl;else cout<<"No"<<endl;

	return 0;
}
