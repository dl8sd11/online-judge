#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    pair<int,int> rem[200003];
    vector<int> ans;
    cin >> n;

    for (int i=1;i<=n;i++) {
        int u,v;
        cin >> u >> v;
        rem[i].first = u;
        rem[i].second = v;
    }

    if (n == 3) {
        cout << "1 2 3" << endl;
        return 0;
    }
    
    int prev = 1;
    for (int i=1;i<=n;i++) {
        int u = rem[prev].first;
        int v = rem[prev].second;
        ans.emplace_back(prev);
        if (rem[u].first == v || rem[u].second == v) {
            prev = u;
        } else {
            prev = v;   
        }
    }

    for (int i=0;i<int(ans.size());i++) {
        cout << ans[i] << " \n"[i==int(ans.size())-1];
    }

}