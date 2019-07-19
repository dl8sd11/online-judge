#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXC = 100005;

bitset<MAXC> sieve;
vector<int> prime;
void linear_sieve () {
    for (ll i=2;i < MAXC;i++) {
        if (!sieve[i]) {
            prime.eb(i);
        }
        for (ll j=0;j<SZ(prime)&&i*prime[j]<MAXC;j++) {
            sieve[i*prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

int t;

ll query(ll x) {
    ll ret = 0;
    cout << 1 << " " << x << endl;
    cin >> ret;
    return ret;
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    linear_sieve();
    cin >> t;
    vector<ll> bprime;
    for (auto p : prime) {
        if (ll(p) * p > 2000000000) {
            bprime.eb(p);
        }
    }
    srand(time(0));
    while (t--) {
        ll cur = 0, mn = 0, x = 44729;
        ll X = query(x);
        cur = x * x - X;
        mn = X;
        vector<ll> fac;
        ll tmp = cur;
        for (auto p : prime) {
            if (p > mn && tmp % p == 0) {
                fac.eb(p);
            }
            while (tmp % p == 0) {
                tmp /= p;
            }
        }
        if (tmp != 1) {
            fac.eb(tmp);
        }
        debug(fac, cur);

        ll tst = 2;
        while (true) {
            vector<ll> res;
            for (auto f : fac) {
                res.eb(tst*tst%f);
            }
            sort(ALL(res));
            bool flag = true;
            REP (i, SZ(res)-1) {
                if (res[i] == res[i+1]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                break;
            }
            tst++;
        }

        ll Y = query(tst);
        cur = __gcd(cur, tst*tst-Y);
        mn = max(mn, Y);

        fac.clear();
        tmp = cur;
        for (auto p : prime) {
            if (p > mn && tmp % p == 0) {
                fac.eb(p);
            }
            while (tmp % p == 0) {
                tmp /= p;
            }
        }
        if (tmp != 1) {
            fac.eb(tmp);
        }

        debug(fac);
        assert(SZ(fac) == 1);
        cout << 2 << " " << fac.back() << endl;
        string res;
        cin >> res;
    }

    return 0;
}
