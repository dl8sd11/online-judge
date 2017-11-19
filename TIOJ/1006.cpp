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
#define MAX 55
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
int a[MAX];
int b[MAX];
int tmp[MAX];
int tmp2[MAX];
int rst[MAX];

void read_big(string str, int *big){
	MEM(big,0);
	int strlen = str.length();
	for(int i=0;i<strlen;i++){
		big[i]=(int)(str[strlen-i-1]-'0');
	}
}
void print_big(int *big){
	int i;
	for(i=MAX;i>0&&big[i]==0;i--);
	while(i>=0){
		cout<<big[i];
		i--;
	}
}
void copy_big(int *a,int *b){
	for(int i=0;i<MAX;i++){
		a[i]=b[i];
	}
}

int compare_big(int *a,int *b){
	int i;
	for(i=MAX;i>0&&a[i]==b[i];i--);
	return a[i]-b[i];
}

int shift_big(int *big,int digi){
	for(int i=MAX-1;i>=digi;i--){
		big[i]=big[i-digi];
	}
	REP(i,digi)
		big[i]=0;
}
int shift1_big(int *big){
	REP(i,MAX-1){
		big[i]=big[i+1];
	}
	big[MAX-1]=0;
}

void sub_big(int *rst,int *a,int *b){
	bool borrow = false;
	for(int i=0;i<MAX;i++){
		rst[i]=a[i]-b[i]-borrow;
		if(rst[i]<0){
			rst[i]+=10;
			borrow = true;
		}
		else
			borrow = false;
	}
}
void muli_big(int *rst,int *big,int x){
	for(int i=0;i<MAX;i++){
		rst[i] = big[i] * x;
	}
	int carry =0;
	for(int i=0;i<MAX;i++){
		rst[i] += carry;
		carry = rst[i]/10;
		rst[i]%=10;
	}
}

int diviez_big(int *a,int *b){
	copy_big(tmp,a);
	int ct =0;
	while(compare_big(tmp,b)>=0){
		sub_big(tmp,tmp,b);
		ct++;
	}
	return ct;
}   //tmp used
int divi_big(int *rst,int *a,int *b,int dgap){
	shift_big(b,dgap);
	while(dgap>=0){
		int Q = diviez_big(a,b);
		rst[dgap] = Q;
		muli_big(tmp2,b,Q);
		sub_big(a,a,tmp2);
		shift1_big(b);
		dgap--;
	}
}
/********** Main()  function **********/
int main()
{
	string x,y;
	cin>>x>>y;
	read_big(x,a);
	read_big(y,b);
	divi_big(rst,a,b,x.length()-y.length());
	print_big(rst);
	return 0;
}
