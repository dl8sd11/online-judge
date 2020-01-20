#include "icc.h"
#include <bits/stdc++.h>
using namespace std;

int djs[102];
int n;

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

bool mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x == y) {
        return false;
    }
    djs[x] = y;
    return true;
}

vector<pair<int,int> > seq;

void buildRoad () {
    for (int i=1;i<=n;i++) {
        djs[i] = i;
        for (int j=1;j<i;j++) {
            seq.emplace_back(j, i);
        }
    }

    printf("%d",int(seq.size()));
    // random_shuffle(seq.begin(), seq.end());
}

pair<int,int> cur;
vector<int> edge[102];

int rcnt = 1;
void newRoad () {
    while (true) {
        int x, y;
        tie(x,y) = seq.back();
        seq.pop_back();
        if (mrg(x, y)) {
            cur = {x, y};
            edge[x].emplace_back(y);
            edge[y].emplace_back(x);
            break;
        }
    }
}

void setRoad(int a, int b) {
    printf("Set %d, %d\n",a,b);
    if (a > b) {
        swap(a, b);
    }
    if (cur == pair<int,int>(a,b)) {
        if (rcnt < n-1) {
            newRoad();
            rcnt++;
        }
    } else {
        printf("Fail!! %d, %d\n",cur.first, cur.second);
        exit(0);
    }
}


int cnt;
int query (int size_a, int size_b, int a[], int b[]) {
    bool res = false;
    cnt++;
    set<int> bs;
    printf("Query:\n");
    for (int i=0;i<size_b;i++) {
        bs.insert(b[i]);
        printf("%d ", b[i]);
    }
    printf("\n");

    for (int i=0;i<size_a;i++) {
        for (auto v : edge[a[i]]) {
            res |= bs.count(v);
        }
        printf("%d ", a[i]);
    }
    printf("\n");

    printf(res?"Yes\n":"No\n");
    return res;
}

int main () {
    int seed = time(0);
    srand(seed);
    scanf("%d",&n);

    printf("N: %d, Seed: %d\n",n,seed);
    buildRoad();
    newRoad();
    run(n);

    printf("AC: %d",cnt);
}
