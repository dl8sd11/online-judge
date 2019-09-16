#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
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
#define TIME(i) Timer i(#i)
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
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 400005;
const int MAXC = 303;

int n, q, len[MAXN * 4], pid[MAXC], inv[MAXC];
bool not_prime[MAXC];
vector<int> prime;

int phi[MAXN * 4], tag[MAXN * 4];
unsigned long long p[MAXN * 4], pt[MAXN * 4], pmask[MAXC];

int mpow(int base,int ep) {
    if (base == 1) {
        return 1;
    }
    int ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ll(ret) * base % MOD;
        }
        base = ll(base) * base % MOD;
        ep >>= 1;
    }
    return ret;
}

void build (int o=1, int l=0, int r=n) {
    if (r == l+1) {
        len[o] = 1;
    } else {
        int m = (l + r) >> 1;
        build(o<<1, l, m);
        build(o<<1|1, m, r);
        len[o] = len[o<<1] + len[o<<1|1];
    }
}

int get (int o) {
    return ll(phi[o]) * mpow(tag[o], len[o]) % MOD;
}

void push (int o) {
    phi[o] = ll(phi[o]) * mpow(tag[o], len[o]) % MOD;
    tag[o<<1] = ll(tag[o<<1]) * tag[o] % MOD;
    tag[o<<1|1] = ll(tag[o<<1|1]) * tag[o] % MOD;
    tag[o] = 1;
    
    p[o] |= pt[o];
    pt[o<<1] |= pt[o];
    pt[o<<1|1] |= pt[o];
}

void pull (int o) {
    phi[o] = ll(get(o<<1)) * get(o<<1|1) % MOD;
    p[o] |= p[o<<1];
    p[o] |= p[o<<1|1];
    p[o] |= pt[o<<1];
    p[o] |= pt[o<<1|1];
}

void mul (int qL, int qR, int v, int o=1, int nL=0, int nR=n) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        pt[o] |= pmask[v];
        tag[o] = ll(tag[o]) * v % MOD;
    } else {
        int nM = (nL + nR) >> 1;
        push(o);
        mul(qL, qR, v, o<<1, nL, nM);
        mul(qL, qR, v, o<<1|1, nM, nR);
        pull(o);
    }
}

int qry (int qL, int qR, unsigned long long &bs, int o=1, int nL=0, int nR=n) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return 1;
    } else if (qL <= nL && nR <= qR) {
        bs |= p[o] | pt[o];
        return get(o);
    } else {
        int nM = (nL + nR) >> 1;
        push(o);
        return ll(qry(qL, qR, bs, o<<1, nL, nM)) * qry(qL, qR, bs, o<<1|1, nM, nR) % MOD;
    }
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    for (int i=2; i<MAXC; i++) {
        if (!not_prime[i]) { // is prime
            pid[i] = SZ(prime);
            prime.eb(i);
            inv[i] = mpow(i, MOD-2);
            for (int j=i; j<MAXC; j+=i) {
                pmask[j] |= (1LL << pid[i]);
                not_prime[j] = true;
            }
        }
    }

    cin >> n >> q;

    fill(phi, phi+MAXN*4, 1);
    fill(tag, tag+MAXN*4, 1);
    build();

    REP (i, n) {
        int d;
        cin >> d;
        if (d > 1) {
            mul(i, i+1, d);
        }
    }

    char str[10];
    while (q--) {
        int l, r, x;
        cin >> str >> l >> r;
        if (str[0] == 'M') {
            cin >> x;
            if (x > 1) {
                mul(l-1, r, x);
            }
        } else {
            unsigned long long ps = 0;
            int ret = qry(l-1, r, ps);
            REP (i, 64) {
                if (ps & (1LL<<i)) {
                    // debug(prime[i]);
                    ret = ll(prime[i] - 1) * inv[prime[i]] % MOD * ret % MOD;
                }
            }
            cout << ret << endl;
        }
    }
    return 0;
}

/*
7 7
119 251 93 98 71 98 175
MULTIPLY 7 7 250
MULTIPLY 5 7 70
MULTIPLY 5 5 242
MULTIPLY 3 3 66
MULTIPLY 4 4 232
MULTIPLY 5 5 232
TOTIENT 2 5

7 3
1 1 1 1 1 1 1
M 4 7 232
M 7 7 2
T 2 5

7 7
119 251 93 98 71 98 175
MULTIPLY 7 7 250
MULTIPLY 5 7 70
MULTIPLY 5 5 242
MULTIPLY 3 3 66
MULTIPLY 4 4 232
MULTIPLY 5 5 232
TOTIENT 2 5int main() - 181 (len[1]) = 7
int main() - 182 (len[2]) = 3

int main() - 205 (prime[i]) = 2
int main() - 205 (prime[i]) = 3
int main() - 205 (prime[i]) = 5
int main() - 205 (prime[i]) = 7
int main() - 205 (prime[i]) = 11
int main() - 205 (prime[i]) = 29
int main() - 205 (prime[i]) = 31
int main() - 205 (prime[i]) = 71
int main() - 205 (prime[i]) = 251
*/