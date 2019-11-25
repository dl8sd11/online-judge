#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2003;
const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;

string a, b;
int len[MAXN][MAXN], cnt[MAXN][MAXN];

void add (int &x, int val) {
    x += val;
    if (x >= MOD) {
        x -= MOD;
    }
}

void upd (pair<int,int> to, pair<int,int> from) {
    int tx, ty, fx, fy;
    tie(tx, ty) = to;
    tie(fx, fy) = from;

    if (len[tx][ty] > len[fx][fy] + 1) {
        len[tx][ty] = len[fx][fy] + 1;
        cnt[tx][ty] = cnt[fx][fy];
    } else if (len[tx][ty] == len[fx][fy] + 1) {
        add(cnt[tx][ty], cnt[fx][fy]);
    }
}

int main () {
    cin >> a >> b;

    memset(len, INF, sizeof(len));
    len[0][0] = 0;
    cnt[0][0] = 1;

    int sa = int(a.size()), sb = int(b.size());
    for (int i=0; i<=sa; i++) {
        for (int j=0; j<=sb; j++) {
            for (char c='a'; c<='z'; c++) { // c++ is awesome!!
                if (c == a[i] && c == b[j]) {
                    upd({i+1, j+1}, {i, j});
                } else if (c == a[i]) {
                    upd({i+1, j}, {i, j});
                } else if (c == b[j]) {
                    upd({i, j+1}, {i, j});
                }
            }
        }
    }

    cout << cnt[sa][sb] << endl;
}