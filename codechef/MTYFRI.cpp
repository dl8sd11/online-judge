#include <bits/stdc++.h>
using namespace std;

int t,n,k,sum1,sum2,tmp;
priority_queue<int,vector<int>,greater<int> > pq2;
priority_queue<int,vector<int>,less<int> > pq1;
void clear(){
  priority_queue<int,vector<int>,greater<int> > cl2;
  priority_queue<int,vector<int>,less<int> > cl1;
  swap(cl1,pq1);
  swap(cl2,pq2);
}
int main(){
  cin>>t;
  while(t--){
    sum1 = 0,sum2 = 0;
    clear();
    cin>>n>>k;
    for(int i=0;i<n;i++){
      cin>>tmp;
      if(i&1){
        sum2+=tmp;
        pq2.push(tmp);
      }else{
        sum1+=tmp;
        pq1.push(tmp);
      }
    }
    if(n==1){
      cout<<"NO"<<endl;
      continue;
    }
    while(k--&&pq1.top()>pq2.top()){
      int t1 = pq1.top(),t2 =pq2.top();
      pq1.pop();
      pq2.pop();
      pq1.push(t2);
      pq2.push(t1);
      sum1 += t2 - t1;
      sum2 += t1 - t2;
    }
    if(sum2>sum1)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;

  }
}
