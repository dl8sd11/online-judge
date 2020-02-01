#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3,unroll-loops,no-stack-protector")

const int INF = 0x3f3f3f3f;
vector<int>  arr;
int sz;
int main () {
    int n;
    cin >> n;

    for (int i=0; i<n; i++) {
        int a, l = -1, r = sz;
        cin >> a;
        while (l < r - 1) {
            int mid = (l + r) >> 1;
            if (arr[mid] < a) {
                r = mid;
            } else {
                l = mid;
            }
        }
        if (r == sz) {
            arr.emplace_back(a);
            sz++;
        } else {
            arr[r] = a;
        }
    }

    cout << sz << endl;

}
