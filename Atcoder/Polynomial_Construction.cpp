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

const int MAXN = 3003;

int p, a[MAXN], inv[MAXN];
int mpow (int bs, int ep) {
    ll ret = 1;
    while (ep) {
        if (ep&1) {
            ret = ret * bs % p;
        }
        bs = bs * bs % p;
        ep >>= 1;
    }
    return ret;
}

int cur[MAXN], tmp[MAXN];
void mul (int c) {
    memset(tmp, 0, sizeof(tmp));
    c = p - c;
    REP (i, p+1) {
        tmp[i] += cur[i] * c % p;
        tmp[i+1] += cur[i];
    }
    REP (i, p+1) {
        cur[i] = tmp[i] % p;
    }
}

int sum[MAXN], res[MAXN];
void divi (int c) {
    int lst = cur[p];
    for (int i=p-1; i>=0; i--) {
        sum[i] = lst;
        lst = (c * lst + cur[i]) % p;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> p;
    REP1 (i, p-1) {
        inv[i] = mpow(i, p-2);
    }

    cur[0] = 1;
    REP (i, p) {
        cin >> a[i];
        mul(i);
    }
#ifdef tmd
    REP (i, p+1) {
        cout << cur[i] << " \n"[i==p];
    }
#endif

    REP (i, p) {
        if (a[i]) {
            int dv = 1;
            REP (j, p) {
                if (i != j) {
                    dv = dv * (i-j) % p;
                }
            }
            if (dv < 0) {
                dv += p;
            }
            dv = mpow(dv, p-2);

            divi(i);
            debug(i);
#ifdef tmd
    for (int i=0; i<p; i++) cout << sum[i] << " \n"[i==p-1];
#endif
            REP (j, p) {
                (res[j] += sum[j] * dv) %= p;
            }
        }
    }

    REP (i, p) {
        cout << res[i] << " \n"[i==p-1];
    }

    REP (i, p) {
        int aa = 0;
        REP (j, p) {
            aa = (aa + res[j]*mpow(i, j)) % p;
        }
        debug(aa, a[i], i);
        assert(aa == a[i]);
    }


}
