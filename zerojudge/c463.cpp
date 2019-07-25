#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 100005;

ll n, h[MAXN], H[MAXN];
bool has_par[MAXN];
vector<ll> edge[MAXN];

void dfs(ll current) {
    for (auto child : edge[current]) {
        dfs(child);
        h[current] = max(h[current], h[child] + 1);
        H[current] += H[child];
    }
    H[current] += h[current];
}

/********** Good Luck :) **********/
int main()
{
    cin.tie(0);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        ll sz, child;
        cin >> sz;
        for (ll j = 1; j <= sz; j++) {
            cin >> child;
            edge[i].push_back(child);
            has_par[child] = true;
        }
    }

    ll root = -1;
    for (ll i = 1; i <= n; i++) {
        if (has_par[i] == false) {
            root = i;
        }
    }

    dfs(root);

    cout << root << endl << H[root] << endl;
    return 0;
}
