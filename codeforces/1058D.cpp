#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,m,k,on,om;
bool used = 0;
bool solve(){
	ll tn = n,tm = m,tk = k;
	tn *= 2;
	ll gcd1 = __gcd(tn,tk);
	tk/=gcd1,tn/=gcd1;
	ll gcd2 = __gcd(tm,tk);
	tk/=gcd2,tm/=gcd2;
	if(tn>n||tk>1)return false;
	on = tn;
	om = tm;
	return true;
}
bool solve2(){
	ll tn = n,tm = m,tk = k;
	tm *= 2;
	ll gcd1 = __gcd(tn,tk);
	tk/=gcd1,tn/=gcd1;
	ll gcd2 = __gcd(tm,tk);
	tk/=gcd2,tm/=gcd2;
	if(tn>n||tk>1)return false;
	on = tn;
	om = tm;
	return true;
}
int main(){
	cin>>n>>m>>k;
	
	
	if(!solve()&&!solve2()){
		cout<<"NO"<<endl;
		return 0;
	}
	
	cout<<"YES"<<endl;
	cout<<"0 0"<<endl;
	cout<<on<<" 0"<<endl;
	cout<<"0 "<<om<<endl;
}