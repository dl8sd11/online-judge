#include <bits/stdc++.h>
using namespace std;
#define SZ(i) int(i.size())

int t, n, p;
vector<pair<int,int> > pg;
int main () {
    cin >> t;
    while (t--) {
        cin >> n;

        pg.clear();
        int lst, cnt = 1;
        cin >> lst;
        if (n == 1) {
            pg.emplace_back(lst, 1);
        }

        for (int i=0; i<n-1; i++) {
            cin >> p;
            if (i == n-2 || p != lst) {
                pg.emplace_back(lst, cnt);
                cnt = 0;
            }
            cnt++;
            lst = p;
        }

#ifdef tmd
        for (auto pa : pg) {
            cout << "{" << pa.first << "," << pa.second << "}\n";
        }
#endif // tmd

        int g = pg.front().second;
        int s = 0, idx = 1, b = 0;
        while (s <= g && idx < SZ(pg)) {
            s += pg[idx].second;
            idx++;
        }
        while (g+s+b+pg[idx].second <= n/2 && idx < SZ(pg)) {
            b += pg[idx].second;
            idx++;
        }

        if (g < s && g < b && g+s+b <= n/2) {
            cout << g << " " << s << " " << b << endl;
        } else {
            cout << "0 0 0" << endl;
        }

    }

}
