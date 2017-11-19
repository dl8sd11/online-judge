 #include <iostream>
 #include <cmath>
 #include <vector>
 #define MAXn 8388607
 typedef long long ll;
using namespace std;
bool sieve[MAXn];
vector<int> prime;
void eratosthenes(){
	sieve[0]=sieve[1]=true;	
	int sqrt_MAXn = sqrt(MAXn);
	for(int i=2;i<=sqrt_MAXn;i++)
		if(!sieve[i])
			for(ll k=(MAXn-1)/i,j=k*i;k>=i;k--,j-=i)
				if(!sieve[j])
					sieve[j]=true;
	
	for(int i=2;i<MAXn;i++)
		if(!sieve[i])
			prime.push_back(i);
	
	
}
int main(){
	eratosthenes();
	int a,b;
	cin>>a>>b;
	
	int start = 0;
	while(prime.at(start)<a)
		start++;
	
	int end = start;
	while(prime.at(end+1)<=b)
		end++;
	
	int ct = 0;
	for(int i=start;i<=end-2;i++){
		for(int j=i+1;j<=i+2;j++)
			if(prime.at(j)-prime.at(i)==4){
				if(ct)
					cout<<",";
				ct++;
				cout<<"("<<prime.at(i)<<","<<prime.at(j)<<")";
			}
				
	}
	if(prime.at(end)-prime.at(end-1)==4){
		cout<<",("<<prime.at(end-1)<<","<<prime.at(end)<<")";
		ct++;
	}
		
	cout<<endl;
	cout<<"¦@"<<ct<<"²Õ"<<endl; 
	
}
