#include <bits/stdc++.h>
using namespace std;
const int MAXN = 52;
typedef bitset<MAXN> bst;
int n,m,ans;
bst edg[MAXN];
bool adj[MAXN][MAXN];
bst emp;
void BronKerbosch (bst R,bst P,bst X) {
  if (P == emp && X == emp) {
    ans = max(ans,int(R.count()));
    return;
  }
  
  int pivot = -1;
  for (int i=0;i<n;i++) {
    if ((P|X)[i]) {
      pivot = i;
    }
  }

  for (int i=0;i<n;i++) {
    if (P[i] && !edg[pivot][i]) {
      R[i] = true;
      BronKerbosch(R,P&edg[i],X&edg[i]);
      R[i] = false;
      P[i] = false;
      X[i] = true;
    }
  }
}

int main () {
  ios_base::sync_with_stdio(0);cin.tie(0);
  while (cin>>n && n ) {
    ans = 0;

    for (int i=0;i<n;i++) {
      for (int j=0;j<n;j++) {
        cin>>adj[i][j];
      }
    }

    for (int i=0;i<n;i++) {
      for (int j=0;j<n;j++) {
        edg[i][j] = adj[i][j];
      }
    }

    bst R,P,X;
    P.flip();
    BronKerbosch(R,P,X);
    cout<<ans<<endl;
  }
}