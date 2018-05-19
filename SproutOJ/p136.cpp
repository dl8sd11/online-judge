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
};
vector<nd> la,ra;
vector<ll> el;
void dfsa(ll A[],ll st,ll idx,ll ed,ll sum){
  if(idx>=ed){
    nd tmp = {sum,el};
    la.push_back(tmp);
    return;
  }
  dfsa(A,st,idx+1,ed,sum);
  el.push_back(A[idx]);
  dfsa(A,st,idx+1,ed,sum+A[idx]);
  if(el.empty())while(1){}
  el.pop_back();
}
void dfsb(ll A[],ll st,ll idx,ll ed,ll sum){
  if(idx>=ed){
    nd tmp = {sum,el};
    ra.push_back(tmp);

    return;
  }
  dfsb(A,st,idx+1,ed,sum);
  el.push_back(A[idx]);
  dfsb(A,st,idx+1,ed,sum+A[idx]);
  if(el.empty())while(1){}
  el.pop_back();
}
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
  el.clear();
  dfsa(A,0,0,N/2,0);
  el.clear();
  dfsb(A,N/2,N/2,N,0);
  sort(la.begin(),la.end(),[](const nd &a,const nd &b){return a.sum<b.sum;});
  sort(ra.begin(),ra.end(),[](const nd &a,const nd &b){return a.sum<b.sum;});
  for (nd x: la){
      ll tg = K - x.sum;
      if(tg==0){
        for(auto _el:x.nel)Report(_el);
        Report(-1);
        return;
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
        return;
      }
  }
  Report(-1);
}
  // Sample test in problem description.
int main() {
  // You may change it to any data that you'd like to test with.
  int N = 40;
  int K = 20968761;
  long long A[] = {289383,930886,692777,636915,747793,238335,885386,760492,516649,641421,202362,490027,368690,520059,897763,513926,180540,383426,89172,455736,5211,595368,702567,956429,465782,21530,722862,665123,174067,703135,513929,979802,634022,723058,133069,898167,961393,18456,175011,478042};
  solve(N, K, A);
  return 0;
}
