#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll x,y,ans=1;
/********** Good Luck :) **********/
int main()
{
    cin >> n;
    for (ll i=0;i<n;i++) {
        ll a,b;
        cin >> a >> b;
        if (x < y) {
            if (a  >=  y) {
                ans += min(a,b)-y+(x!=y);
            }
            x = a;
            y = b;
        } else {
            if (b >= x) {
                ans += min(a,b)-x+(x!=y);
            }
            x = a;
            y = b;
        }
    }

    cout << ans << endl;
    return 0;
}
