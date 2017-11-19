#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	string input;
	cin>>input;
	int i;
	for(i=0;i<input.length();i++){
		if(input.at(i)==':')
			break;
	}
	string hr = input.substr(0,i);
	string min = input.substr(i+1,input.length()-i-1);
	int ihr;
	int imin;
	stringstream hs;
	hs<<hr;
	hs>>ihr;
	stringstream hm;
	hm<<min;
	hm>>imin;
	
	if(ihr>=12)ihr-=12;
	float ans = abs(ihr*30 + imin * 0.5 - imin*6);
	if(360-ans<ans)ans=360-ans;
	cout<<fixed<<setprecision(2)<<ans<<endl;
}

