#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops,no-stack-protector")
using namespace std;
typedef long long ll;
typedef long long lld;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#define ALL(a) a.begin(),a.end()
#define all(a) (a).begin(), (a).end()
#define SZ(a) ((int)a.size())
#define F first
#define S second
#define ff first
#define ss second
#define REP(i,n) for(int i=0;i<((int)n);i++)
#define eb emplace_back
#define pb push_back
#define MP(a,b) make_pair(a,b)
#define SORT_UNIQUE(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#define GET_POS(c,x) (int)(lower_bound(c.begin(),c.end(),x)-c.begin())
#define EL cout<<'\n'
#define BS(a,x) binary_search(ALL(a),x)
template<typename T1,typename T2>
ostream& operator<<(ostream& out,pair<T1,T2> P){
	out<<'('<<P.F<<", "<<P.S<<')';
	return out;
}
template<typename T>
ostream& operator<<(ostream& out,vector<T> V){
	REP(i,SZ(V)) out<<V[i]<<((i!=SZ(V)-1)?" ":"");
	return out;
}
//}}}
const ll maxn=300005;
const ll maxlg=20;
const ll INF64=1e18;
const int INF=0x3f3f3f3f;
const ll MOD=ll(1e9+7);
const ld PI=acos(-1);
const ld eps=1e-9;
//const ll p=880301;
//const ll P=31;

ll mypow(ll a,ll b){
	ll res=1LL;
	while(b){
		if(b&1) res=res*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return res;
}

const int MAXN = 100005;
const int MAXS = 51;
int dp[MAXS][MAXN]; // dp[i][j] := max type 2 if pick i stones 

int main(){
	IOS;
    int n, k, g1, g2, g3;
    cin >> n >> k >> g1 >> g2 >> g3;

    
    string str(n+1, '0');
    int dc =0;

    for (int i=1; i<MAXS; i++) {
        dp[i][0] = -(MAXN);
    }
    for (int i=1; i<=n; i++) {
        cin >> str[i];
        dc += str[i] == '.';
        for (int j=0; j<MAXS; j++) {
            dp[j][i] = dp[j][i-1];
            if (i >= 2 && str[i] == '.' && str[i-1] == '.') {
                dp[j][i] = max(dp[j][i], dp[j][i-2]+1);
            }
            if (i >= 3 && j > 0 && str.substr(i-2, 3) == ".#.") {
                dp[j][i] = max(dp[j][i], dp[j-1][i-3]);
            }
        }
    }

    int ans = 0;
    for (int i=0; i<MAXS; i++) {
        int c = dp[i][n];
        int r = dc - c*2 - i*2;

        if (c >= 0) {
            for (int cc=0; cc<=c; cc++) {
                int nc = c - cc;
                int nr = r + cc * 2;

                nr = min(nr, k);
                ans = max(g1*nr + g2*nc + g3*i, ans);
            }
        }
    }
    cout << ans << endl;
	
	return 0;
}

