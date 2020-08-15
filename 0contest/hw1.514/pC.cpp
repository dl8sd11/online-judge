#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

const int MOD = 1000000009;
const int M = 1000000007;
const int maxn = 2e5 + 5;

int cm[128];
int cnt[3][maxn];
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    string s;
    cin>>n>>s;

    cm['J']=0;
    cm['O']=1;
    cm['I']=2;
    int b[3]={M,MOD-1,MOD-M+1};
    map<int,vector<int>> pos;
    pos[0].emplace_back(0);
    int sum=0;
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<3;j++){
            cnt[j][i]=cnt[j][i-1];
        }
        cnt[cm[s[i-1]]][i]++;
        sum=(sum+b[cm[s[i-1]]])%MOD;
        for(int p:pos[sum]){
            if(i-p<=ans)break;
            bool f=true;
            for(int j=0;j<3;j++){
                f&=cnt[j][i]-cnt[j][p]==(i-p)/3;
            }
            if(f)ans=i-p;
        }
        pos[sum].emplace_back(i);
    }
    cout<<ans<<endl;
}
