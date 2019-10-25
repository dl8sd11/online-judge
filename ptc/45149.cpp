#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define double long double
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

const int MAXN = 11;
const ll MOD = 1000000007;

int t, n;
const double eps = 0.0000000000001;
double c, e[MAXN], pi = acos(-1);

double crad (double r, double l) {
    return 2*asin(l/2/r);
}

double srad (double m) {
    double rad = 0;
    REP (i, n) {
        rad += crad(m, e[i]);
    }
    return rad - 2 * pi;
}

double drad (double m) {
    double rad = 0;
    REP (i, n) {
        rad += crad(m, e[i]) * (i==n-1?-1:1);
    }
    return rad;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> c >> n;
        REP (i, n) {
            cin >> e[i];
        }
        sort(e, e+n);

        double cr = c / 2 / pi;

        double ca = cr*cr*pi;
        double pa = 0;
        debug(srad(e[n-1]/2), drad(e[n-1]/2));
        if (srad(e[n-1]/2) > 0) {
            double l = e[n-1]/2, r = cr;
            while (l < r - eps) {
                double m = (l + r) / 2;

                if (srad(m) < 0) {
                    r = m;
                } else {
                    l = m;
                }
            }
            REP (i, n) {
                pa += sqrt(l*l-e[i]*e[i]/4)*e[i]/2;
            }
        } else {
            double l = e[n-1]/2, r = cr;
            while (l < r - eps) {
                double m = (l + r) / 2;

                if (drad(m) > 0) {
                    r = m;
                } else {
                    l = m;
                }
            }

            REP (i, n) {
                pa += sqrt(l*l-e[i]*e[i]/4)*e[i]/2 * (i==n-1?-1:1);
            }
        }

        cout << fixed << setprecision(20) << ca - pa << endl;
    }
    return 0;
}
/*
1
31.463 4
3.01 5 1.458 2.23

*/
