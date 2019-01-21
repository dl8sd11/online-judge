#include <bits/stdc++.h>
using namespace std;

int n;
set<long long> ans;
void solve(int val) {
    long long m = n / val;
    ans.insert((2+(m-1)*val)*m/2);
}
int main () {
    cin >> n;

    for (int i=1;i*i<=n;i++) {
        if (n % i == 0) {
            solve(i);
            solve(n/i);
        }
    }
    bool fst = true;
    for (auto e:ans) {
        if (!fst) {
            cout << " ";
        }
        cout << e;
        fst = false;
    }
    cout << endl;
}