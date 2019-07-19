/*input
6
2 1
2 50
4 2
5 5
42 48
47 38
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
#define REP(i,j,k)     for(int i = j ; i < k ; ++i)
#define RREP(i,j,k)    for(int i = j ; i >=k ; --i)
#define A    first
#define B    second
#define mp   make_pair
#define pb   emplace_back
#define PII pair<int , int>
#define MEM(i,j)   memset(i , j , sizeof i)
#define ALL(i)     i.begin() , i.end()
#define DBGG(i,j)     cout << i << " " << j << endl
#define DB4(i,j,k,l)  cout << i << " " << j << " " << k << " " << l << endl
#define IOS cin.tie(0) , cout.sync_with_stdio(0)
#define endl "\n"
///------------------------------------------------------------
#define MAX 
#define INF 0x3f3f3f3f

int t , n , m;
int32_t main(){
	IOS;
	cin >> t;
	REP(times , 1 , t + 1){
		cin >> n >> m;
		cout << "Case #" << times << ": " ;
		int final = n;
		if(n > 2 && m > 2){
			n = min(n , m);
			int v1 = m , v2 = 0 , pos = m - 1;
			REP(i , 2 , n + 1) v2 += pos , pos --;
			if(v2 - v1 > 0){
				cout << v2 - v1 << endl;
				// cout << n << endl;
				// pos = m - 1;
				// REP(i , 2 , n + 1){
				// 	int aa = i - 1 , bb = i;
				// 	if(bb == n) bb = final;
				// 	cout << aa << " " << bb << " " << pos << endl , pos --;
				// }
				// cout << 1 << " " << final << " " << m << endl;
			}
			else {
				cout << 0 << endl;
				cout << 1 << endl;
				cout << 1 << " " << final << " " << 1 << endl;
			}
		}
		else {
			cout << 0 << endl;
			cout << 1 << endl;
			cout << 1 << " " << final << " " << 1 << endl;
		}
	}
    return 0;
}