#include <bits/stdc++.h>
using namespace std;

int n, m, ns, ms;

int c[3000], b[3000];
int main () {

    cin >> n;

    for (int lst = 0, i=0; i<n; i++) {
        char ch;
        int d;
        cin >> ch >> d;

        for (int j=0; j<d; j++) {
            c[lst++] = ch == 'W';
        }

        ns = lst;
    }

    cin >> m;
    for (int lst = 0, i=0; i<m; i++) {
        char ch;
        int d;
        cin >> ch >> d;

        for (int j=0; j<d; j++) {
            b[lst++] = ch == 'W';
        }

        ms = lst;
    }

    set<pair<int,int> > cnt;

    int s0 = 0, s1 = 0;
    for (int i=0; i<ns; i++) {
        for (int j=i; j<ns; j++) {

            if (c[j]) {
                s0++;
            } else {
                s1++;
            }

            cnt.insert({s0, s1});
        }
    }

    int ans = 0;

    s0 = s1 = 0;
    for (int i=0; i<ms; i++) {
        for (int j=i; j<ms; j++) {
            if (b[j]) {
                s0++;
            } else {
                s1++;
            }

            if (cnt.count(pair<int,int>(s0, s1))) {
                ans = max(ans, s0 + s1);
            }
        }
    }
    cout << ans << endl;


}
