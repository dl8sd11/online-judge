#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string a,b;
set<char> cnt[27];
set<char> cnt2[27];

int main(){
	cin>>a>>b;
	for(ll i=0;i<ll(a.size());i++){
		cnt[a[i]-'a'].insert(b[i]);
		cnt2[b[i]-'a'].insert(a[i]);
	}

	for(ll i=0;i<26;i++){
		if(cnt[i].size()>1||cnt2[i].size()>1){
			cout<<"No"<<endl;
			return 0;
		}
	}

	cout<<"Yes"<<endl;
	return 0;
}