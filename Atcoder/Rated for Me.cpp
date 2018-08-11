  #include <bits/stdc++.h>
  #include <bits/stdc++.h>
  using namespace std;
  typedef pair<int,int> pii;
  typedef long long ll;
  #define REP(i,n) for(int i=0;i<n;i++)
  #define REP1(i,n) for(int i=1;i<=n;i++)
  #define ALL(i) i.begin(),i.end()
  #define pb push_back
  #define eb emplace_back
  #define X first
  #define Y second

  const int MAXN = 21;
  const ll MOD = 1000000007;
  int n;
  int c[MAXN];

  int main(){
  	ios_base::sync_with_stdio(0);cin.tie(0);
  	cin>>n;
  	REP(i,n)cin>>c[i];
  	ll ans = 1;
  	for(int i=n-1;i>=1;i--)if(c[i-1]>=(i&1?5:2))c[i-1]= (c[i-1]+c[i]*(i&1?ll(5):2))%MOD,c[i]=0;
  	REP(i,n)ans = ans*(c[i]+1)%MOD;
  //	REP(i,n)cout<<val[i]<<" ";
  //	REP(i,n)cout<<c[i]<<" ";
  	if(--ans<0)ans+=MOD;
  	cout<<ans<<endl;
  	return 0;
  }  using namespace std;

  int r;
  int main(){
    cin>>r;
    if(r<1200)cout<<"ABC\n";
    else if(r<2800)cout<<"ARC\n";
    else cout<<"AGC\n";
  }
