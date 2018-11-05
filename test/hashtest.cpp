#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll crush[1000017];
ll valc;
ll c = 26,mod = 1000007;
ll hashfc(string s){
  ll szs = s.length();
  valc = 1;
  ll ret = s[szs-1];
  for(ll i=szs-2;i>=0;i--){
    valc *= c;
    valc %= mod;
    ret += valc*s[i];
    ret %= mod;
  }
  return ret;
}
string s="@@@@@@@@";
void permu(ll len,ll idx){
  if(idx==len){
    string sub = s.substr(0,len);
    crush[hashfc(sub)]++;
    if(hashfc(sub)==188992)cout<<sub<<endl;
    return;
  }
  for(ll i=0;i<52;i++){
    if(i<26)s[idx] = char(i+'a');
    else s[idx] = char(i-26+'A');
    permu(len,idx+1);
  }
}
int main(){
  cout<<hashfc("a")<<endl;
  cout<<hashfc("ab")<<endl;
  for(int i=1;i<6;i++){
    cout<<i<<endl;
    permu(i,0);
  }
  ll maxid = 0;
  for(int i=0;i<1000007;i++)if(crush[i]>crush[maxid])maxid = i;
  cout<<maxid<<endl;
  cout<<crush[maxid]<<endl;
}
