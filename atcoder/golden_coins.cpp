#include <iostream>
using namespace std;

int main () {
    int n;
    cin >> n;

    int sum = n/500 * 1000;
    n = n % 500;
    sum += n / 5 * 5;

    cout << sum << endl;
}
