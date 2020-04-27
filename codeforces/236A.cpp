#include <iostream>
#include <algorithm>
using namespace std;

int main () {
    string name;
    cin >> name;

    sort(name.begin(),name.end());
    int dis = unique(name.begin(),name.end())-name.begin();

    if (dis & 1) {
        cout << "IGNORE HIM!" << endl;
    } else {
        cout << "CHAT WITH HER!" << endl;
    }
}
