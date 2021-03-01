#include <iostream>
#include <string>
typedef long long ll;
using namespace std;

int main(){
string n;
cin>>n;
int lenN = n.length();
for(int i=lenN-1;i>=0;i--){
	cout<<n[i];
}
cout<<endl;
}

