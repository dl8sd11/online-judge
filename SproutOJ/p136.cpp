#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll rsum = 0;
void Report(int id) {
  if(id==-1)cout<<rsum<<endl;
  else rsum+=id;
  fprintf(stderr, "Report(%d)\n", id);
}
struct nd{
  ll sum;
  int nel;
  nd(){sum=0;}
};
vector<nd> la,ra;

void solve(int N,ll K,ll A[]){
  la.clear();
  ra.clear();

  if(N==1){
    Report(A[0]);
    Report(-1);
    return;
  }


  for(ll i=0;i<(1<<N/2);i++){
    nd tmp;
    tmp.sum = 0;
    for(ll j=0;j<N/2;j++){
      if(1<<j&i){
        tmp.sum+=A[j];
      }
    }
    tmp.nel = i;
    la.push_back(tmp);
  }

  ll rsz = N - N/2;
  for(ll i=0;i<(1<<rsz);i++){
    nd tmp;
    tmp.sum = 0;
    for(ll j=0;j<rsz;j++){
      if(1<<j&i){
        tmp.sum+=A[j+N/2];
      }
    }
    tmp.nel = i;
    ra.push_back(tmp);
  }
  // while(1){} pass
  sort(la.begin(),la.end(),[](const nd &a,const nd &b){return a.sum<b.sum;});
  sort(ra.begin(),ra.end(),[](const nd &a,const nd &b){return a.sum<b.sum;});
  // cout<<"LA cnt "<<la.size()<<endl;
  // for(ar:la){
  //   cout<<"sum:"<<ar.sum<<endl;
  //   for(j:ar.nel)cout<<j<<' ';
  //   cout<<endl;
  // }
  // cout<<"RA cnt "<<ra.size()<<endl;
  // for(ar:ra){
  //   cout<<"sum:"<<ar.sum<<endl;
  //   for(j:ar.nel)cout<<j<<' ';
  //   cout<<endl;
  // }
  for (nd x: la){

      ll tg = K - x.sum;

      ll l=0,r=ra.size();
      while(r-l>1){
        ll mid = (l+r)/2;
        if(ra.at(mid).sum>tg)r=mid;
        else l = mid;
      }

      nd y;
      // try{
        y= ra.at(l);
      // } catch(...){
      //   while(1){}
      // }
      //pass

      if(y.sum==tg){
        for(int i=0;i<N/2;i++)if(1<<i&x.nel)Report(A[i]);
        for(int i=0;i<N-N/2;i++)if(1<<i&y.nel)Report(A[i+N/2]);
        Report(-1);
        break;
      }
  }
}
  // Sample test in problem description.
int main() {
  // You may change it to any data that you'd like to test with.
  for(int x=0;x<1;x++){
    long long A[40];
    long long n,k;
    cin>>n>>k;
    cout<<n<<' '<<k<<endl;
    for(int i=0;i<n;i++){
      cin>>A[i];
    }

    solve(n,k, A);
  }
  return 0;
}
