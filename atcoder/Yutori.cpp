#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
int pre[MAXN], suf[MAXN];
string s;

int main () {
    int n, k, c;
    cin >> n >> k >> c;
    cin >> s;

    int lst = -c-1, sum = 0;
    for (int i=0; i<n; i++) {
        if (s[i] == 'o' && i - lst > c) {
            lst = i;
            sum++;
        }
        pre[i] = sum;
    }

    lst = n+c+1, sum = 0;
    for (int i=n-1; i>=0; i--) {
        if (s[i] == 'o' && lst - i > c) {
            lst = i;
            sum++;
        }
        suf[i] = sum;
    }

    assert(pre[n-1] >= k && suf[0] >= k);
    for (int i=0; i<n; i++) {
        if (s[i] == 'o' && (i?pre[i-1]:0) + suf[i+1] < k) {
            cout << i + 1 << endl;
        }
    }
}
