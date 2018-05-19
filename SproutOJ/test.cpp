#include <bits/stdc++.h>
using namespace std;


int main()
{
  cout<<RAND_MAX<<endl;
  int sum = 0;
  for(int i=0;i<40;i++){
    int tmp = rand()%1000000;
    sum+=tmp;
    cout<<tmp<<',';
  }
  cout<<endl<<sum<<endl;
	return 0;
}
