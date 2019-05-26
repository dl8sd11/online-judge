#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f(x) ((x * x + c) % n)

ll n, len;
bool neg = false;
double k, result;
vector<pair<ll, ll> > prime_divs, poly;

ll mypow(ll, ll, ll);
bool miller_rabin(ll, ll);
bool isprime(ll);
ll pollard_rho(ll, ll);
ll expo(ll);
void factorize(ll);
void rotate(ll[], ll);
bool poly_expo(pair<ll, ll>, pair<ll, ll>);
void polynomial();

int main() {
while(cin >> n >> k) {
        if(n == 0) {
            cout << "Result >> 0.0000000000\n----------\n";
            continue;
        }
        if(n < 0) {
            n = -n;
            neg = true;
        }

result = 0;

        factorize(n);
    len = prime_divs.size();

    cout << "Prime Divisors: ";
    for(int i = 0; i < len; i++) {
    printf("%5d ", prime_divs[i].first);
    }
    cout << endl;
    cout << "Prime Div expo: ";
    for(int i = 0; i < len; i++) {
    printf("%5d ", prime_divs[i].second);
    }
    cout << "\n\n";

    ll exponent[len];
    rotate(exponent, 0);

            polynomial();
        
            for(int i = 0; i < poly.size(); i++) {
                result += poly[i].second * pow(k, poly[i].first);
            }
        
            result /= n * 2;
            if(neg && result != 0) result = -result;

    if(!k) cout << "\n\nResult >> 0.0000000000\n----------\n";
    else printf("\n\nResult >> %.10f\n----------\n", result);

    prime_divs.clear();
    poly.clear();
            neg = false;
        }
    return 0;
}

ll mypow(ll base, ll exp, ll md) {
    if(exp == 1) return base % md;
    ll hlf = mypow(base, exp >> 1, md);
    return (exp & 1 ? hlf * hlf % md * base % md : hlf * hlf % md);
}

bool miller_rabin(ll m, ll primes) {
    if(m < 2) return false;
    ll u = m - 1, t = 0;
    while(!(u & 1)) u >>= 1, t++;
    ll x = mypow(primes, u, m);
    if(x == 1 || x == m - 1) return true;
    for(ll i = 0; i < t - 1; i++) {
        x = x * x % m;
        if(x == 1) return false;
        if(x == m - 1) return true;
    }
    return false;
}

bool isprime(ll m) {
    vector<ll> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    if(m < 1000) {
        for(int i = 2; i * i <= m; i++) {
            if(m % i == 0) return false;
        }
        return true;
    }
    bool ret = 1;
    for(ll i = 0; i < primes.size(); i++) {
        if(primes[i] != m) {
            ret &= miller_rabin(m, primes[i]);
        }
    }
    return ret;
}

ll pollard_rho(ll m, ll c) {
    if(m < 1000) {
        for(int i = 2;i * i <= m; i++) {
            if(m % i == 0) return i;
        }
        return m;
    }
    ll a0 = rand() % (m - 1) + 1;
    ll x = a0, y = a0;
    while(true) {
        x = f(x);
        y = f(f(y));
        if(x == y) return m;
        ll d = __gcd(abs(x - y), m);
        if(d > 1 && d < m) return d;
    }
    return -1;
}

ll expo(ll m) {
    ll ntp = n;
    ll q = 0;
    while(ntp % m == 0) {
        ntp /= m;
        q++;
    }
    return q;
}

void factorize(ll m) {
    if(m == 1) return;
    if(isprime(m)) {
        for(int i = 0; i < prime_divs.size(); i++) {
            if(m == prime_divs[i].first) return;
        }
        ll q = expo(m);
        prime_divs.push_back({m, q});
        return;
    }
    ll d = m;
    for(ll c = 0; d == m; ++c)
        d = pollard_rho(m, c);
    factorize(d);
    factorize(m / d);
}

void rotate(ll exponent[], ll j) {
    if(j == len) {
        int d = 1;
        for(int i = 0; i < len; i++) {
            d *= pow(prime_divs[i].first, exponent[i]);
        }
        int phi = n / d;
        for(int i = 0; i < len; i++) {
            if(prime_divs[i].second - exponent[i] != 0) {
                phi = phi * (prime_divs[i].first - 1) / prime_divs[i].first;
            }
        }
        if(neg) poly.push_back({-d, phi});
        else poly.push_back({d, phi});
        return;
    }else {
        for(int i = 0; i <= prime_divs[j].second; i++) {
            exponent[j] = i;
            rotate(exponent, j + 1);
        }
    }
}

bool poly_expo (pair<ll, ll> i, pair<ll, ll> j) {
    return (i.first > j.first);
}

void polynomial() {
    if(neg) n = -n;
    if(n % 2 == 0) {
        bool a = false, b = false;
        for(int i = 0; i < poly.size(); i++) {
            if(poly[i].first == n / 2) {
                poly[i].second += n / 2;
                a = true;
            }else if(poly[i].first == n / 2 + 1) {
                poly[i].second += n / 2;
                b = true;
            }
        }
        if(!a) poly.push_back({n / 2, n / 2});
        if(!b) poly.push_back({n / 2 + 1, n / 2});
    }else {
        bool a = false;
        for(int i = 0; i < poly.size(); i++) {
            if(poly[i].first == (n + 1) / 2) {
                poly[i].second += n;
                a = true;
            }
        }
        if(!a) poly.push_back({(n + 1) / 2, n});
    }
    sort(poly.begin(), poly.end(), poly_expo);
   
    cout << "[";
    for(int i = 0; i < poly.size() - 1; i++) {
        printf("(%d * k ^ %d) + ", poly[i].second, poly[i].first);
    }
    printf("(%d * k ^ %d)] / ", poly[poly.size() - 1].second, poly[poly.size() - 1].first);
    if(neg) printf("(%d)", n * 2);
    else printf("%d", n * 2);
    if(neg) n = -n;
}