#include <bits/stdc++.h>
using namespace std;

struct Snake {
    int hx, hy, tx, ty;
    Snake (int hxi, int hyi, int txi, int tyi) {
        pair<int, int> hd = {hxi, hyi}, tl = {txi, tyi};
        if (hd > tl) {
            swap(hd, tl);
        }
        tie(hx, hy) = hd;
        tie(tx, ty) = tl;
    }

    bool operator < (const Snake &s) const {
        int v1 = hx + hy * 100 + tx * 10000 + ty * 1000000;
        int v2 = s.hx + s.hy * 100 + s.tx * 10000 + s.ty * 1000000;
        return v1 < v2;
    }

    bool l () {
        return hy == ty;
    }
};
map<Snake, int> dis;
vector<vector<int>> grid;
int n;

bool ept(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n && grid[x][y] == 0;
}
/********** Good Luck :) **********/
int main () {


    cin >> n;
    for (int i=0; i<n; i++) {
        vector<int> cur;
        for (int j=0; j<n; j++) {
            int d;
            cin >> d;
            cur.emplace_back(d);
        }
        grid.emplace_back(cur);
    }


    dis[Snake(0, 0, 0, 1)] = 0;
    queue<Snake> bfs;
    bfs.emplace(0, 0, 0, 1);

    while (bfs.size()) {
        Snake cur = bfs.front();
        bfs.pop();


        int cd = dis[cur];
        if (ept(cur.hx, cur.hy+1) && ept(cur.tx, cur.ty+1)) {
            if (dis.count(Snake(cur.hx, cur.hy+1, cur.tx, cur.ty+1)) == 0) {
                bfs.emplace(cur.hx, cur.hy+1, cur.tx, cur.ty+1);
                dis[Snake(cur.hx, cur.hy+1, cur.tx, cur.ty+1)] = cd + 1;
            }
        }
        if (ept(cur.hx+1, cur.hy) && ept(cur.tx+1, cur.ty)) {
            
            if (dis.count(Snake(cur.hx+1, cur.hy, cur.tx+1, cur.ty)) == 0) {
                bfs.emplace(cur.hx+1, cur.hy, cur.tx+1, cur.ty);
                dis[Snake(cur.hx+1, cur.hy, cur.tx+1, cur.ty)] = cd + 1;
            }
        }

        if (cur.l()) {
            if (ept(cur.hx, cur.hy+1) && ept(cur.tx, cur.ty+1)) {
                if (dis.count(Snake(cur.hx, cur.hy, cur.tx-1, cur.ty+1)) == 0) {
                    bfs.emplace(cur.hx, cur.hy, cur.tx-1, cur.ty+1);
                    dis[Snake(cur.hx, cur.hy, cur.tx-1, cur.ty+1)] = cd + 1;
                }
            }
        } else {
            if (ept(cur.hx+1, cur.hy) && ept(cur.tx+1, cur.ty)) {
                if (dis.count(Snake(cur.hx, cur.hy, cur.tx+1, cur.ty-1)) == 0) {
                    bfs.emplace(cur.hx, cur.hy, cur.tx+1, cur.ty-1);
                    dis[Snake(cur.hx, cur.hy, cur.tx+1, cur.ty-1)] = cd + 1;
                }
            }
        }
    }

    if (dis.count(Snake(n-1, n-2, n-1, n-1)) == 0) {
        cout << -1 << endl;
    } else {
        cout << dis[Snake(n-1, n-2, n-1, n-1)] << endl; 
    }
    return 0;
}
