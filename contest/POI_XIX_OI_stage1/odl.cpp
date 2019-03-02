#include <bits/stdc++.h>
using namespace std;
typedef int ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define SZ(i) ll(i.size())
#define MEM(i,n) memset(i,(n),sizeof(i))
#define X first
#define Y second
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template <typename T> void _do(T &&x){cerr<<x<<endl;}
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const ll INF = 0x3f3f3f3f;
const ll MAXN = 1000003;

ll n,v[MAXN];
vector<ll> prime;
bool sieve[MAXN];

void linear_sieve() {
    for (ll i=2;i<1000;i++) {
        if (!sieve[i]) {
            prime.emplace_back(i);
        }
        for (ll j=0;j<SZ(prime)&&prime[j]*i<1000;j++) {
            sieve[prime[j]*i] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
vector<pair<ll,ll> > dv[MAXN]; 
void fac(ll idx) {
    REP (i,SZ(prime)) {
        ll cnta = 0;
        while (v[idx] % prime[i] == 0) {
            cnta++;
            v[idx] /= prime[i];
        }
        if (cnta) {
            dv[idx].emplace_back(prime[i],cnta);
        }
    }
    if (v[idx] != 1) {
        dv[idx].emplace_back(v[idx],1);
    }
}
int main () {
    IOS();
    linear_sieve();
    cin >> n;
    REP (i,n) {
        cin >> v[i];
        fac(i);
    }

    REP (i,n) {
        pair<ll,ll> mn = {INF,INF};
        REP (j,n) {
            if (i != j) {
                ll d = 0;
                ll idx1 = 0,idx2 = 0;
                while (idx1 < SZ(dv[i])) {
                    while (idx2 < SZ(dv[j]) && dv[j][idx2].X < dv[i][idx1].X) {
                        d += dv[j][idx2++].Y;
                    }
                    if (idx2 < SZ(dv[j]) && dv[i][idx1].X == dv[j][idx2].X) {
                        d += abs(dv[i][idx1].Y - dv[j][idx2].Y);
                        idx2++;
                    } else {
                        d += dv[i][idx1].Y;
                    }
                    idx1++;
                }
                while (idx2 < SZ(dv[j])) {
                    d += dv[j][idx2++].Y;
                }

                if (d < mn.X) {
                    mn = {d,j};
                }
            }
        }
        cout << mn.Y + 1<< endl;
    }
}