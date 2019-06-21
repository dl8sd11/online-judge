#include <algorithm>
#include <iostream>

int n,a[100];
int main () {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::sort(a,a+n);
    for (int i = 0; i < n; i++) {
        if (i == n - 1) {
            std::cout << a[i] << std::endl;
        } else {
            std::cout << a[i] << " ";
        }
    }
}