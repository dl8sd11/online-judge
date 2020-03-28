#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)

const int MAXN = 200005;
const ll MOD = 1000000007;

int n, k;
int a[MAXN];
ll sum;
/*********************GoodLuck***********************/
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    REP (i, n) {
        cin >> a[i];
    }

    for (int i=0; i<n-k+1; i++) {
        for (int j=0; j<k/2; j++) {
            sum += abs(a[i+j] - a[i+k-j-1]);
        }
    }

    cout << sum << endl;
}
