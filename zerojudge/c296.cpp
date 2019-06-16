#include <bits/stdc++.h>
int n,m,k,lst;

int main()
{
    std::cin >> n >> m >> k;
    for (int i=n-k+1; i <=n; i++) {
        lst = (lst + m) % i;
    }
    std::cout << lst+1 << std::endl;
    return 0;
}
