#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


ll n,a[103];
deque<ll> ans;
/********** Good Luck :) **********/
int main()
{
    cin >> n;
    for (ll i=0;i<n;i++) {
        cin >> a[i];
    }
    sort(a,a+n);
    
    ans.emplace_back(a[0]);
    for (ll i=1;i<=n-1;i++) {
        if (i&1) {
            ans.push_front(a[i]);
        } else {
            ans.push_back(a[i]);
        }
    }
    for (auto v : ans) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
