#include <iostream>
#include <vector>
using namespace std;

int n,v,a[20];
vector<int> state;
vector<vector<int> > ans;
void dfs(int idx,int sum) {
    if (idx == n) {
        if (sum == v) {
            ans.emplace_back(state);
        }
        return;
    }
    for (int i=0;i<=a[idx];i++) {
        state.emplace_back(i);
        dfs(idx+1,sum^i);
        state.pop_back();
    }
}
int main () {
    cin >> n >> v;
    for (int i=0;i<n;i++) {
        cin >> a[i];
    }
    dfs(0,0);

    cout << ans.size() << endl;
    for (auto aa : ans) {
        for (int i=0;i<int(aa.size());i++) {
            cout << aa[i] << "^="[i==int(aa.size())-1];
        }
        cout << v << endl;
    }
}