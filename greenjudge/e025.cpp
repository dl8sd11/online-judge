#include <iostream>
#include <vector>
#include <algorithm>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
		
	int n;
	cin>>n;
	REP(i,n){
		vector<int> tsk;
		vector<bool> pter;		
		
		
		int input;
		cin>>input;
		int tskPtr= 0;
		while(input){
			if(input==-1){
				pter.push_back(0);
				
			}
			else if(input==-2){
				pter.push_back(1);
			}
			else{
				tsk.push_back(input);
			}
			sort(tsk.begin(),tsk.end());
			
			while(pter.size()&&(tsk.size()-tskPtr)){
				
				if(pter.front()){
					cout<<tsk.back()<<" ";
					tsk.pop_back();
					pter.erase(pter.begin());
				}
				else{
					cout<<tsk.at(tskPtr)<<" ";
					tskPtr++;
					pter.erase(pter.begin());
				}
			}
			
			cin>>input;
		}
		cout<<endl;
	}
	
	
}

