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

const int MAXN = 500005;

ll l, a, b;
ll mod;

int dig (ll x) {
    int cnt = 0;
    while (x) {
        cnt++;
        x /= 10;
    }
    return cnt;
}

ll calc (ll i) {
    return a+b*i;
}

struct Matrix {
    ll dt[3][3];
    Matrix& operator = (const Matrix &other) {
        REP (i, 3) {
            REP (j, 3) {
                dt[i][j] = other.dt[i][j];
            }
        }
        return *this;
    }

	void check () const {
		REP (i, 3) {
			REP (j, 3) {
				assert(dt[i][j] < mod);
			}
		}
	}

    Matrix operator * (const Matrix &other) {
        Matrix res;
		this->check();
		other.check();
        REP (i, 3) {
            REP (j, 3) {
                res.dt[i][j] = 0;
                REP (k, 3) {
                    res.dt[i][j] = (res.dt[i][j]+dt[i][k] * other.dt[k][j]) % mod;
                }
            }
        }
        return res;
    }
};

ostream& operator << (ostream &os,const Matrix& m) {
    return os << m.dt[0][0] << "," << m.dt[0][1] << "," << m.dt[0][2] << "|" << m.dt[1][0] << "," << m.dt[1][1] << "," << m.dt[1][2] << "|" << m.dt[2][0] << "," << m.dt[2][1] << "," << m.dt[2][2] << "|";
}

ll mpow (ll base, ll ep) {
    ll ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = ret * base % mod;
        }
        base = base * base % mod;
        ep >>= 1;
    }
    return ret;
}

ll solve (ll f, ll t) {
    // debug(calc(f), calc(t));
    Matrix tr, res;
    memset(res.dt, 0, sizeof(res.dt));
    REP (i, 3) {
        res.dt[i][i] = 1;
    }
    tr.dt[0][0] = mpow(10, dig(calc(f)));
    tr.dt[0][1] = tr.dt[0][2] = tr.dt[1][2] = tr.dt[2][0] = 0;
    tr.dt[1][0] = tr.dt[1][1] = tr.dt[2][2] = 1;
    tr.dt[2][1] = b % mod;
	// res.check(), tr.check();

    //debug(tr);
    ll dl = t - f + 1;
    // debug(dl,t , f);
    while (dl) {
        if (dl & 1) {
            res = res * tr;
        }
        tr = tr * tr;
        dl >>= 1;
    }
    //debug(res);
    //debug(tr);

    Matrix init;
	memset(init.dt, 0, sizeof(init.dt));
    init.dt[0][0] = 0, init.dt[0][1] = (calc(f)%mod), init.dt[0][2] = 1;
	init.check();
    init = init * res;

    return init.dt[0][0];
}


/*********************GoodLuck***********************/
int main () {
    IOS();
	srand(time(0));

#ifdef tmdd
	l = rand()% 1000000000;
	a = rand() % 1000000000;
	b = (1000000000000000000LL-a)/(l-1);
	mod = 1000000000;
#else
	cin >> l >> a >> b >> mod;
#endif
	ll cur = l-1;
	ll tot = 1;
	ll ans = 0;
	while (cur >= 0) {
		ll L = -1, R = cur;
		while (L < R - 1) {
			ll M = (L + R) >> 1;
			if (dig(calc(M)) == dig(calc(cur))) {
				R = M;
			} else {
				L = M;
			}
		}
		// debug(tot, R, cur);
		ll ret = solve(R, cur);
		debug(cur-R+1, calc(R), ret);
		// debug(ret, tot);
		ans = (ans + tot * ret) % mod;
		tot = tot * mpow(mpow(10, cur - L),dig(calc(cur))) % mod;
		cur = L;
	}

	cout << ans << endl;

}
