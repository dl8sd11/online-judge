#include <iostream>
using namespace std;

 
int main () {
    int n;

    cin >> n;
    
    
    int sum[3] = {};
    for (int i=0; i<n; i++) {
        for (int j=0; j<3; j++) {
            int d;
            cin >> d;

            sum[j] += d;
        }
    }

    bool flag = true;
    for (int i=0; i<3; i++) {
        flag &= sum[i] == 0;
    }
    cout << (flag ? "YES" : "NO") << endl;
}
