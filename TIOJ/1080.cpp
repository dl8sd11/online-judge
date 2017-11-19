
#include <algorithm>
#include <stdio.h>
using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/


#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)




int solve(int n){
	int s[n];
	int total =0;
	REP(i,n){ //s[0]~s[i-1] is sorted
		scanf("%d",s+i);
		int tmp = s[i];

		int *up  = upper_bound(s,s+i-1,s[i]);
		int j= up-s;
		total+=i-j;
		RFOR(k,i,j+1,1){
			s[k]=s[k-1];
		}
		s[j] = tmp;

	}

	printf("%d\n",total );

}
/********** Main()  function **********/
int main()
{
	int n;
	scanf("%d",&n);
	while(n){
		solve(n);
		scanf("%d",&n);
	}
	return 0;
}
