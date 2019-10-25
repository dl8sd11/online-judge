#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000006;
int n, p[MAXN], t, ans[MAXN], iq, stk[MAXN], top;
bool q[MAXN];

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++) {
        cin >> p[i];
    }
    cin >> t;
    for (int i=1; i<=t; i++) {
        cin >> iq;
        q[iq] = true;
    }

    for (int i=n; i>=1; i--) {
        if (top == 0 || stk[top-1] != p[i] || q[i]) {
            stk[top++] = p[i];
            ans[i] = -p[i];
        } else {
            top--;
            ans[i] = p[i];
        }
    }

    if (top == 0) {
        cout << "YES" << endl;
        for (int i=1; i<=n; i++) {
            cout << ans[i] << " \n"[i==n];
        }
    } else {
        cout << "NO" << endl;
    }
}
