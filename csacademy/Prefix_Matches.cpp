#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100001;

int n;
int z[MAXN],f[MAXN];
int main () {
    cin >> n;
    for (int i=1;i<n;i++) {
        cin >> z[i];
        f[i+z[i]-1] = max(f[i+z[i]-1],z[i]);
    }

    for (int i=n-1;i>0;i--) {
        f[i] = max(f[i+1]-1,f[i]);
    }
    for (int i=1;i<n;i++) {
        cout << f[i] << " \n"[i==n-1];
    }
}