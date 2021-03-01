#include<bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define pb push_back
typedef long long ll;
using namespace std;

char ans[2000005];

int main(){
	int n;
	cin>>n;
	
	vector<string> t;
	int maxLen = 0;
	REP(i,n){
		string tmp;
		cin>>tmp;
		t.pb(tmp);
		int tmpLen = tmp.length();
		int m;
		cin>>m;
		
		for(int j=0;j<m;j++){
			int pos;
			cin>>pos;
			
			int newLen = pos + tmp.length() -1;
			if (newLen > maxLen){				
				int lenGap = newLen - maxLen;
				maxLen = newLen;
				for(int k=0;k<lenGap;k++){
					ans += 'a';
				}			
			}
			
			for(int k=0;k<tmpLen;k++){
				ans[pos-1+k] = tmp[k];
			}
		}
	}
	cout<<ans<<endl;

}

