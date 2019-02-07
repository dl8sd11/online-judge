#include <iostream>
#include <iomanip>
using namespace std;

int main () {
    int n, k,cnt[1000];
    cin >> n >> k;
    for (int i=0;i<k;i++) {
        cin >> cnt[i];
    }
    long long ep = 0;
    for (int i=0;i<k;i++) {
        for (int j=0;j<i;j++) {
            ep += cnt[i] * cnt[j];
        }
    }
    cout << fixed << setprecision(5) << double(n-1) * ep / n / (n-1) * 2;
}