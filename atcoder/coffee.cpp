#include <iostream>
using namespace std;

int main () {
    char c[7];
    cin >> c;

    cout << (c[2]==c[3]&&c[4]==c[5] ? "Yes" : "No") << endl;
}
