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

const int MAXN = 100005;
const ll MOD = 1000000007;


typedef array<int,102> ar;

int n;
ar a, b;

int sz;
pii opr[202];

void rev(int l, int r) {
    if (l < r) {
        reverse(b.begin()+l,b.begin()+r+1);
        opr[sz++] = {l,r};
    }
}

int solve () {
    int l = rand() % (n-1);
    int r = l+1;

    sz = 0;

    b = a;
    while (l != 0 || r != n-1) {
        bool gr = rand() % 2;

        if (l == 0 || (r!=n-1 && gr)) {
            if (b[l] > b[r]) {
                int c;
                for (c=l;c<=r; c++) {
                    if (b[c]<b[r+1]) {
                        break;
                    }
                }
                rev(c,r);
                rev(c,r+1);
            } else {
                int c;
                for (c=l;c<=r; c++) {
                    if (b[c]>b[r+1]) {
                        break;
                    }
                }
                rev(c,r);
                if (c != l) {
                    rev(c,r+1);
                }
            }
            r++;
        } else {
            if (b[l] > b[r]) {
                int c;
                for (c=r;c>=l; c--) {
                    if (b[c]>b[l-1]) {
                        break;
                    }
                }
                rev(l,c);
                rev(l-1,c);
            } else {
                int c;
                for (c=r;c>=l; c--) {
                    if (b[c]<b[l-1]) {
                        break;
                    }
                }
                rev(l,c);
                if (c != r) {
                    rev(l-1,c);
                }
            }
            l--;
        }
    }

    if (b[l] > b[r]) {
        rev(l, r);
    }

    return sz;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    srand(time(0));

    cin >> n;
    REP (i, n) {
        #ifdef tmd
        a[i] = i+1;
        #else
        cin >> a[i];
        #endif // tmd
    }
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }
    #ifdef tmd
    random_shuffle(a.begin(),a.begin()+n);
    #endif // tmd

    int mn = MOD;
    while (true) {
        int cur = solve();
        debug(cur);
        mn = min(cur, mn);
        if (cur < 191) {
            break;
        }
    }

    cout << mn << endl;
    REP (i, mn) {
        cout << opr[i].X+1 << " " << opr[i].Y+1 << endl;
    }

    debug(mn);
    sort(a.begin(),a.begin()+n);
    assert(a == b);
}
