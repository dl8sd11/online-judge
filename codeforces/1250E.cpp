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

const int MAXN = 61;
const ll MOD = 1000000007;

int t, n, m, k;
string nec[MAXN], rnec[MAXN];

int djs[MAXN*2], rev[MAXN*2], lk[MAXN*2];
vector<int> el[MAXN*2];

int fnd (int x) {
    return djs[x] == x ? x : djs[x] = fnd(djs[x]);
}

void mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x == y) {
        return;
    }
    djs[x] = y;
    rev[y] += rev[x];
}

bool conf (const string &s1, const string &s2) {
    int cnt = 0;
    REP (i, m) {
        cnt += s1[i] == s2[i];
    }
    return cnt < k;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n >> m >> k;

        REP (i, n) {
            cin >> nec[i];
            rnec[i] = nec[i];
            reverse(ALL(rnec[i]));
        }

        REP (i, n) {
            djs[i*2] = i*2;
            djs[i*2+1] = i*2+1;
            rev[i*2] = 0;
            rev[i*2+1] = 1;
            lk[i*2] = 0;
            lk[i*2+1] = 0;
            el[i*2].clear();
            el[i*2+1].clear();
        }

        REP (i, n) {
            REP (j, n) {
                if (conf(nec[i], nec[j])) {
                    mrg(i*2, j*2+1);
                    mrg(i*2+1, j*2);
                }
                if (conf(nec[i],rnec[j])) {
                    mrg(i*2, j*2);
                    mrg(i*2+1, j*2+1);
                }
            }
        }

        bool ans = true;
        REP (i, n) {
            if (fnd(i*2) == fnd(i*2+1)) {
                ans = false;
            }
            el[fnd(i*2+1)].eb(i+1);
        }

        int mn = 0;
        vector<int> sel;

        REP (i, n) {
            if (!lk[fnd(i*2)]) {
                assert(!lk[fnd(i*2+1)]);
                int x = fnd(i*2), y = fnd(i*2+1);

                mn += min(rev[x], rev[y]);
                if (rev[x] > rev[y]) {
                    for (auto v : el[y]) {
                        sel.eb(v);
                    }
                } else {
                    for (auto v : el[x]) {
                        sel.eb(v);
                    }
                }
                lk[x] = lk[y] = true;
            }
        }

        if (ans == false) {
            cout << -1 << endl;
        } else {
            assert(SZ(sel) == mn);
            cout << SZ(sel) << endl;
            REP (i, mn) {
                cout << sel[i];
                if (i != mn-1) {
                    cout << " ";
                }
            }
            cout << endl;
        }

    }


}
