#include <iostream>
#include <cmath>
using namespace std;
#define SZ(a) int(a.size())
int main () {
    int n, ans[100005];
    bool isInt[100005];
    long long sum = 0; 
    cin >> n;
    for (int i=0;i<n;i++) {
        double d;
        cin >> d;
        sum += floor(d);
        isInt[i] = d - floor(d) < 1e-7;
        ans[i] = floor(d);
    }
    
    for (int i=0;i<n;i++) {
            if (!isInt[i] && sum++ < 0) {
                    ans[i]++;
            }
    }
    for (int i=0;i<n;i++) {
        cout << ans[i] << endl;
    }
}
