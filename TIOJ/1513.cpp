#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast","unroll-loops")

int n;
unsigned int ans, tmp;
/*********************GoodLuck***********************/
int main () {
    while (scanf("%d",&n) != EOF) {
        ans = 0;
        for (int i=0; i<n; ++i) {
            scanf("%u",&tmp);
            ans ^= tmp;
        }
        printf("%u\n",ans);
    }
}
