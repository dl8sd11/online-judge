#include <stdio.h>
#include <algorithm>
using namespace std;
typedef int ll;
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define REP(i, j) FOR(i, 0, j, 1)

const ll MAXN=2e5+5;

ll t,n,m;
ll djs[MAXN],sz[MAXN];

void init() {
    for (int i=0;i<MAXN;i++) {
        djs[i] = i;
        sz[i] = 1;
    }
}

ll fnd(ll x) {
    return x == djs[x] ? x : fnd(djs[x]);
}

void uni(ll x,ll y) {
    if (sz[x=fnd(x)] > sz[y=fnd(y)]) {
        swap(x,y);
    }
    djs[x] = y;
    sz[y] += sz[x];
}

ll hei(ll x) {
    ll ret = 0;
    while (x != djs[x]) {
        ret++;
        x = djs[x];
    }
    return ret;
}
/********** Good Luck :) **********/
int main()
{
    scanf(" %d",&t);
    while (t--) {
        scanf(" %d%d",&n,&m);
        init();
        REP (x,m) {
            char c;
            int u,v;
            scanf(" %c%d%d",&c,&u,&v);
            if (c == 'D') {
                if(fnd(u) != fnd(v)) {
                    uni(u,v);
                }
            } else {
                if (fnd(u) != fnd(v)) {
                    printf("Not sure yet.\n");
                } else {
                    if (abs(hei(u) - hei(v))&1) {
                        printf("In different gangs.\n");
                    } else {
                        printf("In the same gang.\n");
                    }
                }
            }
        }
    }
    return 0;
}

//WA