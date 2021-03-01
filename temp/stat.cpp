#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main(int argc, char *argv[]) {
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  t++;

  vector<int> a(n+2), b(m), T(n+2);
  vector<vector<int> > pre(2, vector<int>(n+2, t*2)), dp(2, vector<int>(n+2, t*2));

  for (int i=0; i<n; i++) {
    cin >> a[i+1];
  }
  a[n+1] = s;

  for (int i=0; i<m; i++) {
    cin >> b[i];
  }

  T[0] = b[0];
  T[n+1] = s - b[m-1];

  int idx = 0;
  for (int i=1; i<=n; i++) {
    while (b[idx+1] < a[i]) {
      idx++;
    }
    T[i] = min(abs(a[i]-b[idx]), abs(a[i]-b[idx+1]));
  }

  int bst_p = 0, bst_q = 0;
  pre[0][0] = T[0];

  for (int i=1; i<=n+1; i++) {
    for (int k=0; k<=n+1; k++) { 
      dp[i&1][k] = t*2;
      if (k >= i) dp[i&1][k] = a[i] + i;
      for (int j=1; j<=i; j++) {
        int tm = a[i] - a[j] + (i-j+1) + T[j];
        if (k >= i-j+1) {
          dp[i&1][k] = min(dp[i&1][k], pre[j&1^1][k-(i-j+1)] + tm);
        }
       
      }
      pre[i&1][k] = dp[i&1][k] + T[i];

    }
    for (int k=0; k<=n+1; k++) pre[i&1][k] = min(pre[i&1^1][k], pre[i&1][k]);
  }

  for (int i=0; i<=n+1; i++) {
    if (dp[n&1^1][i] <= t) {
      bst_p = i;
      bst_q = dp[n&1^1][i];
    }
  }

  cout << bst_p - 1 << " " << bst_q - 1 << endl;
  return 0;
}

