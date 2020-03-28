#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define eb emplace_back
#define X first
#define SZ(i) int(i.size())
#define Y second
#define ALL(i) i.begin(),i.end()
#define MEM(i,a) memset(i,(a),sizeof(i))
#ifdef tmd
#define debug(...) fprintf(stderr,"%d(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x) {
    cerr<<x<<endl;
}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {
    cerr<<x<<",";
    _do(y...);
}
template<typename IT> ostream& _print(IT bg, IT ed, ostream &os) {
    for (IT it=bg;it!=ed; it++) {
        if (it==bg) {
            os << "{" << *it;
        } else {
            os << "," << *it;
        }
    }
    return os << "}";
}
template<typename IT> void pary (IT bg, IT ed) {
    _print(bg, ed, cerr);
}
template<typename T> ostream& operator<< (ostream &os, const vector<T> &vec) {
    return _print(vec.begin(), vec.end(),os);
}
#define IOS()
#else
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#define pary(...)
#endif // tmd

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

const int MAXN = 1000004;

int t;
int n;
string str;

typedef array<ll,2> ai2;
const ai2 C = {880301, 9167};
const ai2 MD = {MOD, 1000000009};

ai2 operator * (const ai2& a1, const ai2 &a2) {
    ai2 ret;
    for (int i=0; i<2; i++) {
        ret[i] = a1[i] * a2[i] % MD[i];
    }
    return ret;
}

ai2 operator + (const ai2& a1, const ai2 &a2) {
    ai2 ret;
    for (int i=0; i<2; i++) {
        ret[i] = (a1[i] + a2[i]) % MD[i];
    }
    return ret;
}

ai2 operator - (const ai2& a1, const ai2 &a2) {
    ai2 ret;
    for (int i=0; i<2; i++) {
        ret[i] = (a1[i] - a2[i]) % MD[i];
        if (ret[i] < 0) {
            ret[i] += MD[i];
        }
    }
    return ret;
}

ai2 pw[MAXN], inv[MAXN];

ll mpow (ll bs, ll ep, ll M) {
    ll res = 1;
    while (ep) {
        if (ep&1) {
            res = res * bs % M;
        }
        bs = bs * bs % M;
        ep >>= 1;
    }
    return res;
}

void build() {
    pw[0] = inv[0] = {1,1};
    for (int i=1; i<MAXN; i++) {
        pw[i] = pw[i-1] * C;
        REP (j, 2) {
            inv[i][j] = mpow(pw[i][j], MD[j]-2, MD[j]);
        }
    }
}

struct HS {
    ai2 pre[MAXN];

    void init (const string &s) {
        pre[0] = {0, 0};
        REP1 (i, SZ(s)) {
            ai2 tmp = {s[i-1],s[i-1]};
            pre[i] = pre[i-1] + pw[i] * tmp;
        }
    }

    HS() {
    }

    ai2 get (int l, int r) {
        ai2 res = pre[r] - pre[l-1];
        return res * inv[l];
    }
};
HS shs;

/*******GOODLUCK*********/
int main () {
    IOS();
    build();

    cin >> t;
    while (t--) {
        #ifdef tmd
        str = "";
        REP (i, 1000000) {
            str += char('a'+rand()%26);
        }
        #else
        cin >> str;
        #endif // tmd
        n = SZ(str);
        shs.init(str);

//        debug(str);

//        cout << solve(1) << endl;

        int bg = 1;
        int ans = 0;
        while (true) {
            if (bg == n/2+1) {
                if (n&1) {
                    ans++;
                }
                break;
            }

            bool flag = false;
            for (int i=1; i+bg-1<=n/2; i++) {
//                debug(i);
                if (shs.get(bg, bg+i-1) == shs.get(n-bg-i+2, n-bg+1)) {
                    ans += 2;
//                    debug(bg, i);
                    bg = bg + i;
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                ans++;
                break;
            }
        }

        cout << ans << endl;
    }

    return 0;
}
