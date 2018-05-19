// Uncomment the following line for local test.
//#define LOCAL_SPROUT
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(int N, long long K, long long A[]);

void Report(int id) {
  fprintf(stderr, "Report(%d)\n", id);
}
struct nd{
  ll sum;
  vector<ll> nel;
  nd(){sum=0;}
};
vector<nd> la,ra;
vector<ll> el;

void solve(int N,ll K,ll A[]){
  la.clear();
  ra.clear();
  if(N==1){
    if(K==A[0]){
      Report(A[0]);
      Report(-1);
    }
    return;
  }


  for(ll i=0;i<(1<<N/2);i++){
    nd tmp;
    for(ll j=0;j<N/2;j++){
      if(1<<j&i){
        tmp.sum+=A[j];
        tmp.nel.push_back(A[j]);
      }
    }
    la.push_back(tmp);
  }

  ll rsz = N - N/2;
  for(ll i=0;i<(1<<rsz);i++){
    nd tmp;
    for(ll j=0;j<rsz;j++){
      if(1<<j&i){
        tmp.sum+=A[j+N/2];
        tmp.nel.push_back(A[j+N/2]);
      }
    }
    ra.push_back(tmp);
  }
  // while(1){}
  sort(la.begin(),la.end(),[](const nd &a,const nd &b){return a.sum<b.sum;});
  sort(ra.begin(),ra.end(),[](const nd &a,const nd &b){return a.sum<b.sum;});
  for (nd x: la){

      ll tg = K - x.sum;
      if(tg==0){
        for(auto _el:x.nel)Report(_el);
        Report(-1);
        break;
      }
      ll l=0,r=ra.size();
      while(r-l>1){
        ll mid = (l+r)/2;
        if(ra[mid].sum>tg)r=mid;
        else l = mid;
      }
      if(ra[l].sum==tg){
        for(auto _el:x.nel)Report(_el);
        for(auto _el:ra[l].nel)Report(_el);
        Report(-1);
        break;
      }
  }
  Report(-1);
}
  // Sample test in problem description.
int main() {
  // You may change it to any data that you'd like to test with.
  int N = 40;
  int K = 20679378;
  long long A[] = {930886,692777,636915,747793,238335,885386,760492,516649,641421,202362,490027,368690,520059,897763,513926,180540,383426,89172,455736,5211,595368,702567,956429,465782,21530,722862,665123,174067,703135,513929,979802,634022,723058,133069,898167,961393,18456,175011,478042};
  solve(N, K, A);
  return 0;
}
