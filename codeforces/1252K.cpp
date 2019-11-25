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

struct Matrix {
    ll dt[2][2];
    Matrix () {
        dt[0][0] = dt[1][1] = 1;
        dt[0][1] = dt[1][0] = 0;
    }

    Matrix operator* (const Matrix &oth) const {
        Matrix ret;
        REP (i, 2) {
            REP (j, 2) {
                ret.dt[i][j] = 0;
                REP (k, 2) {
                    ret.dt[i][j] += dt[i][k]*oth.dt[k][j];
                    ret.dt[i][j] %= MOD;
                }
            }
        }
        return ret;
    }

    void flip() {
        swap(dt[0][0], dt[1][1]);
        swap(dt[0][1], dt[1][0]);
    }

    pair<int,int> eval (int a, int b) {
        return {(a*dt[0][0]+b*dt[1][0])%MOD, (a*dt[0][1]+b*dt[1][1])%MOD};
    }

    void print() {
#ifdef tmd
        cout << "Matrix:" << endl;
        cout << dt[0][0] << " " << dt[0][1] << endl;
        cout << dt[1][0] << " " << dt[1][1] << endl;
#endif
    }
} A, B, I;

int n, q;
string state;
Matrix seg[MAXN*4];
bool rev[MAXN*4];

Matrix getTrans(int o) {
    Matrix ret = seg[o];
    if (rev[o]) {
        ret.flip();
    }
    return ret;
}

void push(int o) {
    if (rev[o]) {
        seg[o].flip();
        rev[o<<1] ^= 1;
        rev[o<<1|1] ^= 1;
        rev[o] = 0;
    }
}

void pull(int o) {
    seg[o] = getTrans(o<<1) * getTrans(o<<1|1);
}

void build (int o, int nL, int nR) {
    if (nL == nR - 1) {
        seg[o] = state[nL] == 'A' ? A : B;
    } else {
        int nM = (nL + nR) >> 1;
        build(o<<1, nL, nM);
        build(o<<1|1, nM, nR);
        pull(o);
    }
}

void chg (int qL, int qR, int o, int nL, int nR) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        rev[o] ^= 1;
    } else {
        int nM = (nL + nR) >> 1;
        push(o);
        chg(qL, qR, o<<1, nL, nM);
        chg(qL, qR, o<<1|1, nM, nR);
        pull(o);
    }
}

Matrix qry (int qL, int qR, int o, int nL, int nR) {
    debug(nL, nR);
    if (qL >= nR || qR <= nL || qL >= qR) {
        return I;
    } else if (qL <= nL && nR <= qR) {
        return getTrans(o);
    } else {
        int nM = (nL + nR) >> 1;
        push(o);
        return qry(qL, qR, o<<1, nL, nM)*qry(qL, qR, o<<1|1, nM, nR);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q;
    cin >> state;

    B.dt[0][1] = A.dt[1][0] = 1;
    A.print(), B.print();
    build(1, 0, n);

    while (q--) {
        int cmd, l, r;
        cin >> cmd >> l >> r;
        l--;
        if (cmd == 1) {
            chg(l, r, 1, 0, n);
        } else {
            int a, b;
            cin >> a >> b;
            Matrix res = qry(l, r, 1, 0, n);

            res.print();
            pair<int,int> ab = res.eval(a, b);

            cout << ab.first << " " << ab.second << endl;
        }
    }

}
