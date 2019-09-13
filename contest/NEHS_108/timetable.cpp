#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define ALL(i) i.begin(),i.end();
#define SZ(i) int(i.size())
#define MEM(i,n) memset(i, (n), sizeof(i))
#define X firsrt
#define Y second
#define eb emplace_back
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ", __PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

int n;
char tb[21][21];

int main () {
	IOS();
	
	cin >> n;
	
	REP (i, 21) {
		REP (j, 21) {
			tb[i][j] = char(32);
		}
	}
	REP (u, n) {
		char c;
		int d, cl, cr;
		cin >> c;
		cin >> d >> cl >> cr;
		for (int i=cl; i<=cr; i++) {
			tb[i][d-1] = c;
		}
		
	}
	
	cout << "|\\|M|T|W|T|F|S|" << endl;
	
	cout << "---------------" << endl;
	
	REP (i, 14) {
		if (i < 10) {
			cout << "|" << i << "|";
		} else if (i == 10) {
			cout << "|X|";
		} else {
			cout << "|" << char(i-11+'A') << "|";
		}
		REP (j, 6) {
			cout << tb[i][j] << "|";
		}
		cout << endl;
	}

	return 0;
}

