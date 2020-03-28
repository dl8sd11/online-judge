#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 300005;
const ll MOD = 1000000007;

int n, m;
ll s[MAXN], a[MAXN];

ll test[MAXN];
void test_add (ll f, ll t, ll a0, ll d) {
    for (ll i=f; i<=t; i++) {
        if (i >= 1 && i <= n) {
            test[i] += a0;
            a0 += d;
        }
    }
}

ll test_qry (ll f, ll t) {
    ll res = 0;
    for (ll i=f; i<=t; i++) {
        res += test[i];
    }
    return res;
}

class Arithmetic_Segment_Tree {
private:
    ll seg[MAXN*4], hd[MAXN*4], dl[MAXN*4];

    ll get (int o, int nL, int nR) {
        return seg[o] + (2*hd[o]+(nR-nL-1LL)*dl[o]) * (nR - nL) / 2;
    }

    void push (int o, int nL, int nR) {
        int nM = (nL + nR) >> 1;
        seg[o] = get(o, nL, nR);
        hd[o<<1] += hd[o];
        dl[o<<1] += dl[o];
        hd[o<<1|1] += hd[o] + dl[o]*(nM - nL);
        dl[o<<1|1] += dl[o];
        hd[o] = 0;
        dl[o] = 0;
    }

    void pull (int o, int nL, int nR) {
        int nM = (nL + nR) >> 1;
        seg[o] = get(o<<1, nL, nM) + get(o<<1|1, nM, nR);
    }

    void atag (int qL, int qR, int a0, int d, int o, int nL, int nR) {
        if (qL >= nR || qR <= nL || qL >= qR) {
            return;
        } else if (qL <= nL && nR <= qR) {
            hd[o] += 1LL * (nL - qL) * d + a0;
            dl[o] += d;
//            debug(nL, nR, hd[o], dl[o]);
//            debug(get(o, nL, nR));
        } else {
            int nM = (nL + nR) >> 1;
            push(o, nL, nR);
            atag(qL, qR, a0, d, o<<1, nL, nM);
            atag(qL, qR, a0, d, o<<1|1, nM, nR);
            pull(o, nL, nR);
        }
    }

    ll qry (int qL, int qR, int o, int nL, int nR) {
        if (qL >= nR || qR <= nL || qL >= qR) {
            return 0;
        } else if (qL <= nL && nR <= qR) {
            return get(o, nL, nR);
        } else {
            int nM = (nL + nR) >> 1;
            push(o, nL, nR);
            return qry(qL, qR, o<<1, nL, nM) + qry(qL, qR, o<<1|1, nM, nR);
        }
    }
public:
    void add (int qL, int qR, int a0, int d) {
        debug(qL, qR, a0, d);
        atag(qL, qR+1, a0, d, 1, 1, n+1);
        #ifdef tmd
        test_add(qL, qR, a0, d);
        #endif // tmd
    }

    ll eval (int qL, int qR) {
        #ifdef tmd
        ll res = test_qry(qL, qR);
        ll me = qry(qL, qR+1, 1, 1, n);
        if (res != me) {
            debug(me, res);
            assert(me == res);
        }

        #endif // tmd
        return qry(qL, qR+1, 1, 1, n+1);
    }
} sum;

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    while (m--) {
        char cmd;
        cin >> cmd;

        if (cmd == 'P') { // add
            int x;
            cin >> x;
            cin >> s[x] >> a[x];
            sum.add(x, x+s[x]/a[x], s[x], -a[x]);
            sum.add(x-s[x]/a[x], x-1, s[x]%a[x], +a[x]);
        } else if (cmd == 'U') { // remove
            int x;
            cin >> x;
            sum.add(x, x+s[x]/a[x], -s[x], a[x]);
            sum.add(x-s[x]/a[x], x-1, -s[x]%a[x], -a[x]);
        } else { // query
            int l, r;
            cin >> l >> r;

            debug(sum.eval(l,r));
            cout << sum.eval(l, r) / (r-l+1) << endl;
        }
    }
}

/*
10 3
P 1 9 3
Q 1 1
Q 1 2

10 10
P 1 35 3
P 10 8 3
P 5 7 2
Q 3 10
*/
