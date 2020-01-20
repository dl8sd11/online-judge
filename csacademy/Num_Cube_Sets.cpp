#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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
template<typename T> ostream &operator << (ostream &os,pair<T,T> &v){return os<<"{"<<v.first<<","<<v.second<<"}";}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif


const int MAXN = 1000006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

#define SQ(i) ((i)*(i))

int t, n , m;
typedef pair<ll,ll> pll;

ll mpow (ll bs, ll ep) {
    ll res = 1;
    REP (i, ep) {
        res = res * bs;
    }
    return res;
}

pair<ll,ll> divi[MAXN];
bool sieve[MAXN];

void init() {
    REP (i, MAXN) {
        divi[i] = {1,1};
    }
    for (int i=2;i<MAXN;i++) {
        if (!sieve[i]) {
            for (int j=i;j<MAXN;j+=i) {
                sieve[j] = true;
                int tmp = j, cnt = 0;
                while (tmp % i == 0) {
                    tmp /= i;
                    cnt++;
                }
                if (cnt % 3 != 0) {
                    divi[j].first *= mpow(i,cnt%3);
                    divi[j].second *= mpow(i,3-cnt%3);
                }
            }
        }
    }
}

pll build (ll val) {
    return divi[val];
}

map<ll,ll> sa, sb;
/*********************GoodLuck***********************/
int main () {
    IOS();
    init();

    cin >> t;
    while (t--) {
        cin >> n >> m;

        sa.clear();
        sb.clear();
        REP (i, n) {
            ll d;
            cin >> d;
            sa[build(d).first]++;
        }
        REP (i, m) {
            ll d;
            cin >> d;
            sb[build(d).first]++;
        }

        ll ans = -1;
        for (auto p : sa) {
            ll cnt = sb[build(p.first).second];
            if (cnt > 0) {
                ans = max(ans, SQ(p.second)+SQ(cnt));
            }
        }

        cout << ans << endl;
    }

}
