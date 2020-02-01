#include <bits/stdc++.h>
using namespace std;

int ans[1000000];
int main () {
    int step = 0;
    int N;
    while (cin >> N) {

        cout << "testcase: " << ++step << endl;
        for (int i=0;i<N;i++) {
            cin >> ans[i];
        }

        for (int i=0;i<N;i++) {
            for (int j=0;j<i;j++) {
                if (ans[i] == ans[j]) {
                    cout << "Error: " << i << " " << j << " are same!" << endl;
                }
            }
        }

        for (int i=0;i<N;i++) {
            if (ans[i] < 1 || ans[i] > 1000000000) {
                cout << "Error: " << i << " exceed limit" << endl; 
            }
        }
        for (int i=0;i<N;i++) {
            if (__gcd(ans[i],ans[(i+1)%N]) == 1) {
                cout << "Error: " << i << " " << (i+1)%N << " coprime" << endl;
            }
            if (__gcd(ans[i],__gcd(ans[(i+1)%N],ans[(i+2)%N])) != 1) {
                cout << "Error: " << i << " " << (i+1)%N << " " << (i+2)%N << " not coprime" << endl;
            }
        }
    }
}
