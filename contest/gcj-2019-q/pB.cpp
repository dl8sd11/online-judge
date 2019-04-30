#include <bits/stdc++.h>
using namespace std;

int t,n;
string p;
int main () {
    cin >> t;
    for (int test_number=1;test_number<=t;test_number++) {
        cin >> n >> p;
        string ans;
        if (p.back() != p.front()) {
            for (int i=1;i<n;i++) {
                ans += p.back();
            }
            for (int i=1;i<n;i++) {
                ans += p.front();
            }
        } else {
            int cnt = 0;
            char op = p.front() == 'S' ? 'E' : 'S';
            for (int i=0;;i++) {
                cnt += (p[i] != p[0]);
                if (p[i] == p[i+1] && p[i] != p.front()) {
                    for (int j=0;j<cnt;j++) {
                        ans += op;
                    }
                    for (int j=0;j<n-1;j++) {
                        ans += p.front();
                    }
                    for (int j=0;j<n-1-cnt;j++) {
                        ans += op;
                    }
                    break;
                }
            }
        }
        cout << "Case #" << test_number << ": " << ans << endl;
    }
}