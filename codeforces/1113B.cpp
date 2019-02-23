#include <bits/stdc++.h>
using namespace std;

int n,sum;
vector<int> a;
int main () {
    cin >> n;
    for (int i=0;i<n;i++) {
        int tmp;
        cin >> tmp;
        a.emplace_back(tmp);
        sum += tmp;
    }

    sort(a.begin(),a.end());

    int ans = sum;
    for (int i=1;i<n;i++) {
        for (int j=2;j*j<=a[i];j++) {
            if (a[i] % j == 0) {
                if (j*j != i) {
                    int k = a[i]/j;
                    ans = min(ans,a[0]*(k-1)-a[i]/k*(k-1)+sum);
                }
                ans = min(ans,a[0]*(j-1)-a[i]/j*(j-1)+sum);
            }
        }
    }

    cout << ans << endl;
}