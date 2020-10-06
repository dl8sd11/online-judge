#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, m, q;
int a[MAXN], seg[MAXN*4], tag[MAXN*4];
vector<vector<int> > replacement;

int getMin(int o) {
    return seg[o] + tag[o];
}

void push(int o) {
    if (tag[o]) {
        seg[o] += tag[o];
        tag[o<<1] += tag[o];
        tag[o<<1|1] += tag[o];
        tag[o] = 0;
    }
}

void pull(int o) {
    seg[o] = min(getMin(o<<1), getMin(o<<1|1));
}

void add(int qL, int qR, int val, int o, int nL, int nR) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] += val;
        return;
    } else {
        int nM = (nL + nR) >> 1;
        push(o);
        add(qL, qR, val, o<<1, nL, nM);
        add(qL, qR, val, o<<1|1, nM, nR);
        pull(o);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> m >> q;

    int gtCnt = 0;
    REP (i, n) {
        cin >> a[i];
        gtCnt += a[i] > a[0];
    }
    int randall = a[0];
    add(0, m, -gtCnt, 1, 0, m);

    REP (i, m) {
        int r, d, cnt = 0;
        vector<int> vec;
        cin >> r;
        REP (j, r) {
            cin >> d;
            vec.emplace_back(d);
            cnt += d > randall;
        }
        replacement.emplace_back(vec);

        add(i, i+1, n-r-1, 1, 0, m);
        add(i+1, m, -cnt, 1, 0, m);
    }

    REP (i, q) {
        int x, y, nw, dl;
        cin >> x >> y >> nw;
        x--, y--;
        dl = (replacement[x][y] > randall) - (nw > randall);
        add(x+1, m, dl, 1, 0, m);
        replacement[x][y] = nw;

        debug(getMin(1));
        cout << (getMin(1) >= 0) << endl;
    }
}
