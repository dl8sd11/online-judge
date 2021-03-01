#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("avx", "avx2", "fma")
#include <iostream>
#include <string>
using namespace std;

string pool[100005];
string *strs[100005];

// std::string please
int main () {

    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> pool[i];
        strs[i] = &pool[i];
    }

    int a, b;
    while (cin >> a >> b) {
        (*strs[a]) += (*strs[b]);
        for (int i=b; i<n-1; i++) {
            strs[i] = strs[i+1];
        }
        strs[n-1] = nullptr;
        n--;
    }
    for (int i=0; i<n; i++) {
        cout << (*strs[i]) << '\n';
    }

}
