#include <bits/stdc++.h>
using namespace std;

int main(){
	string a;
	cin>>a;
	int alen = int(a.size());
	int ans = 0;
	for (int i = 0; i < alen - 2; i++) {
		for (int j = i + 1; j < alen - 1; j++) {
			for (int k = j + 1; k < alen; k++){
				if (a.at(i) == 'Q' && a.at(j) == 'A' && a.at(k) == 'Q') ans++;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
