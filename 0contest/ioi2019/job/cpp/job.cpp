#include "job.h"
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

long long scheduling_cost(std::vector<int> p, std::vector<int> u, std::vector<int> d) {

    int n = p.size();

    vector<int> idx;
    for (int i=1; i<n; i++) {
        idx.emplace_back(i);
    }

    sort(idx.begin(), idx.end(), [&] (int i, int j) {
        return 1LL*d[i]*u[j] < 1LL*d[j]*u[i];
    });

    ll ans = u[0]*d[0], sum = d[0];

    for (auto v : idx) {
        sum += d[v];
        ans += sum * u[v];
    }

    return ans;
}
