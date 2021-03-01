#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,sum;
/********** Good Luck :) **********/
int main()
{
    cin >> n;
    for (ll i=2;i<=n;i++) {
        sum += (n/i + 1) * (n / i) / 2 - 1;
    }
    cout << sum * 4 << endl;
    return 0;
}
