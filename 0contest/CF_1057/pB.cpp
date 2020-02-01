#include <bits/stdc++.h>
using namespace std;

int n,r[5003],pre[5003],ans;
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);

  cin>>n;
  for (int i = 1; i <= n; i++) {
    cin >> r[i];
    pre[i] += r[i] + pre[i-1];
  }

  for (int i = 1; i <= n; i++) {
    for (int j=1; j <= i; j++) {
      if (pre[i] - pre[j-1] > 100 * (i - j + 1)) {
        ans = max(ans,i - j + 1);
      }
    }
  }

  cout << ans << endl;
}
