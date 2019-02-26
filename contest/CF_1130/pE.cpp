#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define SZ(i) ll(i.size())
ll k;
vector<ll> ans;
/********** Good Luck :) **********/
int main()
{
    cin >> k;
    ll s = -1;
    ans.emplace_back(-1);
    while (SZ(ans)+k-1 > s) {
        ll cur = min(1000000LL,SZ(ans)+k-s);
        ans.emplace_back(cur);
        s += cur;
    }
    cout << SZ(ans) << endl;
    for (auto v : ans) {
        cout << v << " ";
    }
    return 0;
}
