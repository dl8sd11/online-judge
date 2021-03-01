#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back

int solve (vector<int> &in) {
    vector<int> res;
    vector<int> adj(in.size() - 1);
    for (int i=0; i<in.size()-1; i++) {
        adj[i] = in[i] + in[i+1];
    }
    int id = min_element(adj.begin(), adj.end()) - adj.begin();
    int ans = adj[id];
    for (int i=0; i<in.size(); i++) {
        if (i == id) res.eb(ans);
        else if (i == id + 1) continue;
        else res.eb(in[i]);
    }
    in = res;
    return ans;
}
int main () {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i=0; i<n; i++) cin >> a[i];
    int ans = 0;
    while (a.size() > 1) {
        ans += solve(a);
    }
    cout << ans << endl;

}
