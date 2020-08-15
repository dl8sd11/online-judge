#include "icc.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 102;
namespace SOL {
    int n;

    int id[MAXN];
    int fnd (int x) {
        return x == id[x] ? x : id[x] = fnd(id[x]);
    }

    bool mrg (int x, int y) {
        x = fnd(x), y = fnd(y);
        if (x == y) {
            return false;
        }
        id[x] = y;
        return true;
    }
    vector<vector<int> > djs;

    void build() {
        djs.clear();
        for (int i=1;i<=n;i++) {
            vector<int> cur;
            for (int j=1;j<=n;j++) {
                if (fnd(j) == i) {
                    cur.emplace_back(j);
                }
            }
            if (cur.size()) {
                djs.emplace_back(cur);
            }
        }
    }
}

int a[MAXN], b[MAXN];
int sz_a, sz_b;
void getGroup () {
    vector<pair<int,int> > gp;

    int gcnt = 0;
    for (auto v : SOL::djs) {
        gp.emplace_back(gcnt++, v.front());
    }

    int mx = __lg(gcnt);

    vector<int> iar;
    for (int i=0;i<=mx;i++) {
        iar.emplace_back(i);
    }
    random_shuffle(iar.begin(),iar.end());

    for (int i:iar) {
        sz_a = 0, sz_b = 0;
        for (int j=0;j<gcnt;j++) {
            if (j & (1<<i)) {
                for (auto v : SOL::djs[gp[j].first]) {
                    a[sz_a++] = v;
                }
            } else {
                for (auto v : SOL::djs[gp[j].first]) {
                    b[sz_b++] = v;
                }
            }
        }
        if (query(sz_a, sz_b,a, b)) {
            break;
        }
    }
}

void shrinkGroup () {
    while (sz_a > 1) {
        int tmp = sz_a / 2;
        if (query(tmp, sz_b, a, b)) {
            sz_a = tmp;
        } else {
            for (int i=0;i<sz_a-tmp;i++) {
                a[i] = a[i+tmp];
            }
            sz_a = sz_a - tmp;
        }
    }
}

void run (int N) {
    SOL::n = N;
    srand(time(0));

    for (int i=1;i<=SOL::n;i++) {
        SOL::id[i] =i;
    }
    SOL::build();

    for (int i=0;i<SOL::n-1;i++) {
        getGroup();
        shrinkGroup();
        swap(sz_a, sz_b);
        swap(a, b);
        shrinkGroup();
        setRoad(a[0], b[0]);
        assert(sz_a == 1 && sz_b == 1);

        SOL::mrg(a[0], b[0]);
        SOL::build();
    }
}
