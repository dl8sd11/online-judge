#include <stdio.h>
#include <algorithm>
using namespace std;
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i, j) FOR(i, 1, j+1, 1)
#define X first
#define Y second


const int MAXN=2e5+5;

int djs[MAXN],sz[MAXN];
int v_cnt = 0;
pair<int,int> p[MAXN];

void init() {
    REP (i,MAXN) {
        djs[i] = i;
        sz[i] = 1;
    }
}

int fnd(int nd) {
    if (djs[nd] == nd) {
        return nd;
    } else {
        return djs[nd] = fnd(djs[nd]);
    }
}

void uni(int x,int y) {
    if (fnd(x) == fnd(y)) {
        return;
    }
    if (sz[x=fnd(x)] < sz[y=fnd(y)]) {
        swap(x,y);
    }
    djs[y] = x;
    sz[x] += sz[y];
}

int t,n,m;
/********** Good Luck :) **********/
int main()
{
    scanf(" %d",&t);
    REP1 (i,MAXN-1) {
        p[i] = {i<<1,i<<1|1};
    }
    while (t--) {
        init();
        scanf(" %d%d",&n,&m);
        while (m--) {
            char c;
            int u,v;
            scanf(" %c%d%d",&c,&u,&v);
            if (c == 'D') {
                uni(p[u].X,p[v].Y);
                uni(p[u].Y,p[v].X);
            } else {
                if (fnd(p[u].X) == fnd(p[v].Y) || fnd(p[u].Y) == fnd(p[v].X)) {
                    puts("In different gangs.");
                } else if (fnd(p[u].X) == fnd(p[v].X) || fnd(p[u].Y) == fnd(p[v].Y)) {
                    puts("In the same gang.");
                } else {
                    puts("Not sure yet.");
                }
            }
        }
    }
    return 0;
}

//WA