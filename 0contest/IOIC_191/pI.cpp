// =＾● ⋏ ●＾=
#include<bits/stdc++.h>
using namespace std;

int a[3636][3636];

int main(){cin.tie(0);
    int n; cin>>n;
    int sum=0;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cin>>a[i][j];
            sum+=a[i][j];
        }
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            cout<<a[j][i]<<" ";
        }
        cout<<endl;
    }
    cout<<sum<<endl;
}