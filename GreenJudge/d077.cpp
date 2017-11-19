  #include <iostream>
  #include <queue>
  using namespace std;

  int main(){
    int n;
    cin>>n;

    int timelen[110000];
    for(int i=0;i<110000;i++){
      timelen[i]=0;
    }

    int s = 0;
    for(int i=0;i<n;i++){
      int a,b;
      cin>>a>>b;
      if(a>s){
        s=a+b-1;
      }
      else{
        for(int j=a;j<=s;j++){
          timelen[j]++;
        }
        s= s+b;
      }

    }
    int ans = 0;
    for(int i=0;i<110000;i++){
      ans = max(ans,timelen[i]);

    }
    cout<<ans<<endl;
  }
