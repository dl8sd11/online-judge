#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
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

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, a[MAXN];
int q;

set<int> rem;

int bit[MAXN];

void add (int x, int val) {
    for (x++;x<MAXN;x+=-x&x) {
        bit[x] += val;
    }
}

int qry (int x) {
    int ret = 0;
    for (x++; x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int qry (int l, int r) {
    return qry(r) - qry(l-1);
}

void chg (int l, int r) {
    while (true) {
        auto ptr = rem.lower_bound(l);
        if (ptr != rem.end() && *ptr <= r) {
            int org = a[*ptr];
            int fnl = int(sqrt(org));
//            debug(*ptr, org, fnl);

            add(*ptr, fnl-org);
            a[*ptr] = fnl;
            l = (*ptr)+1;
            if (fnl == 1) {
                rem.erase(ptr);
            }
        } else {
            break;
        }
    }
}
/*********************GoodLuck***********************/
signed main () {
    IOS();

    int t = 0;
    while (cin >> n) {
        t ++;
        rem.clear();
        memset(bit, 0, sizeof(bit));

        REP (i, n) {
            cin >> a[i];
            rem.insert(i);
            add(i, a[i]);
        }

        cin >> q;

        cout << "Case #" << t << ":" << endl;
        while (q--) {

            int cmd, l, r;
            cin >> cmd >> l >> r;
            l--, r--;
            if (l > r) {
                swap(l, r);
            }

            if (cmd == 0) { // modify
                chg(l, r);
            } else {
                cout << qry(l, r) << endl;
            }
        }
        cout << endl;

    }


}
