#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#define REP(i,n) for(int i=0;i<n;i++)
#define PI 3.14159265
typedef long long ll;
using namespace std;

int main(){
	double a,b,c;
	double d;
	cin>>a>>b>>c;
	
	d=(sin(b*PI/180)*sin(c*PI/180))/sin((b+c)*PI/180)*a;
	cout<<fixed<<setprecision(2)<<d;
}

