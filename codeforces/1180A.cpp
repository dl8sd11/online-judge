#include <iostream>
using namespace std;

int main () {
    int n;
    cin >> n;
    int hf = (1 + 2*n-1) * n / 2;
    cout << hf * 2 - 2*n+1 << endl;
}