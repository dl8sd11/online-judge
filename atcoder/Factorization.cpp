#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAXN = 100000;
const ll MOD = 1000000007;
vector<ll> prime;
bool sieve[MAXN];
void linear_sieve(){
	for(ll i=2;i<MAXN;i++){
		if(!sieve[i])prime.emplace_back(i);
		for(ll j=0;j<ll(prime.size())&&i*prime[j]<MAXN;j++){
			sieve[prime[j]*i] = 1;
			if(i%prime[j]==0)break;
		}
	}
}


ll myexp(ll b,ll p){
  if(p==1)return b;
  ll tmp = myexp(b,p/2);
  tmp = tmp*tmp%MOD;
  return p&1?tmp*b%MOD:tmp%MOD;
}
ll inv(ll a){
  return myexp(a,MOD-2);
}

ll c(ll cn,ll cm){
	
	ll ret = 1;
	for(ll i=1;i<=cm;i++){
		ret = (ret*(cn-i+1))%MOD;
		ret = ret*inv(i)%MOD;
	}
	return ret;
}
ll n,m,ans;
int main(){
	cin>>n>>m;
	linear_sieve();
	ll pidx = 0;
	ans = 1;
	while(m!=1){
		ll cnt = 0;
		while(m%prime[pidx]==0)m/=prime[pidx],cnt++;
		ans = ans*c(n+cnt-1,cnt)%MOD;
		if(++pidx >= prime.size()-1)break;
	}
	if(m!=1)ans = ans*n%MOD;

	cout<<ans<<endl;
}