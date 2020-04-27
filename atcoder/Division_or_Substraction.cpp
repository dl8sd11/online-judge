#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
vector<pair<ll,int> > fac;

set<int> ans;
int pw[50];

ll mpow (ll bs, ll ep) {
    if (ep == 0) {
        return 1;
    } else {
        ll hf = mpow(bs, ep>>1);
        return (ep&1) ? hf*hf*bs : hf*hf;
    }
}
void dfs (int id) {
    if (id == int(fac.size())) {
        int gcd = pw[0];

        for (int i=0; i<int(fac.size()); i++) {
            gcd = __gcd(gcd, pw[i]);
        }

        for (int i=1; i<=gcd; i++) {
            if (gcd % i == 0) {
                ll k = 1;
                ll ky = 1;
                for (int j=0; j<int(fac.size()); j++) {
                    k *= mpow(fac[j].first, pw[j] / i);
                    ky *= mpow(fac[j].first, pw[j]);
                }

                if (n/ky % k == 1) {
                    ans.insert(k);
                }
            }
        }
    } else {
        for (int i=0; i<=fac[id].second; i++) {
            pw[id] = i;
            dfs(id+1);
        }
    }
}
int main () {
    cin >> n;

    ll tmp = n;
    for (ll i=2; i*i<=n; i++) {
        if (tmp % i == 0) {
            int cnt = 0;
            while (tmp % i == 0) {
                cnt++;
                tmp /= i;
            }
            fac.emplace_back(i, cnt);
        }
    }
    if (tmp != 1) {
        fac.emplace_back(tmp, 1);
    }

    dfs(0);

    n--;
    for (ll i=1; i*i<=n; i++) {
        if (n % i == 0) {
            ans.insert(i);
            ans.insert(n/i);
        }
    }
    ans.erase(1);

    cout << ans.size() << endl;
}
