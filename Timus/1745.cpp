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
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1003;
const int MAXC = 10004;
const ll MOD = 1000000007;

struct Wrd {
    int from, dl, id, len;
    bool operator < (const Wrd &wd) {
        if (from != wd.from) {
            return from < wd.from;
        } else {
            return dl > wd.dl;
        }
    }
};

vector<Wrd> L, R;

int n;
int dpL[MAXN][MAXC], dpR[MAXN][MAXC];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP1 (i, n) {
        string str;
        cin >> str;
        int cnt = 0, l = 0;
        for (auto c : str) {
            if (c == ')') {
                if (cnt == 0) {
                    l++;
                } else {
                    cnt--;
                }
            } else {
                cnt++;
            }
        }
        int r = cnt;
        if (l > r) {
            R.push_back({r, l-r, i, SZ(str)});
        } else {
            L.push_back({l, r-l, i, SZ(str)});
        }
    }

    sort(L.begin(), L.end());
    sort(R.begin(), R.end());

    for (auto V : L) {
        debug(V.id);
    }
    for (auto V : R) {
        debug(V.id, V.from, V.dl);
    }

    REP (i, MAXC) {
        dpL[0][i] = -MOD;
        dpR[0][i] = -MOD;
    }

    dpL[0][0] = 0;
    REP (i, SZ(L)) {
        for (int j=0; j<MAXC; j++) {
            dpL[i+1][j] = dpL[i][j];
            if (j-L[i].dl >= L[i].from) {
                dpL[i+1][j] = max(dpL[i+1][j], dpL[i][j-L[i].dl]+L[i].len);
            }
        }
    }

    dpR[0][0] = 0;
    REP (i, SZ(R)) {
        for (int j=0; j<MAXC; j++) {
            dpR[i+1][j] = dpR[i][j];
            if (j-R[i].dl >= R[i].from) {
                dpR[i+1][j] = max(dpR[i+1][j], dpR[i][j-R[i].dl]+R[i].len);
            }
        }
    }

    int ans = 0;
    REP (i, MAXC) {
        if (dpL[SZ(L)][i] + dpR[SZ(R)][i] > dpL[SZ(L)][ans] + dpR[SZ(R)][ans]) {
            ans = i;
        }
    }
    vector<int> ansL, ansR;
    int i = SZ(L), tmp = ans, clen = dpL[SZ(L)][ans];
    while (i != 0) {
        i--;
        if (tmp-L[i].dl >= L[i].from && dpL[i][tmp-L[i].dl]+L[i].len == clen) {
            ansL.emplace_back(L[i].id);
            clen = dpL[i][tmp-L[i].dl];
            tmp = tmp - L[i].dl;
        }
    }


    i = SZ(R), tmp = ans, clen = dpR[SZ(R)][ans];
    while (i != 0) {
        i--;
        if (tmp-R[i].dl >= R[i].from && dpR[i][tmp-R[i].dl]+R[i].len == clen) {
            ansR.emplace_back(R[i].id);
            clen = dpR[i][tmp-R[i].dl];
            tmp = tmp - R[i].dl;
        }
    }


    reverse(ansL.begin(), ansL.end());
    for (auto v : ansR) {
        ansL.emplace_back(v);
    }


    cout << dpL[SZ(L)][ans] + dpR[SZ(R)][ans] << " " << SZ(ansL) << endl;
    REP (j, SZ(ansL)) {
        cout << ansL[j] << " \n"[j==SZ(ansL)-1];
    }

}
/*
5
(((
)((
))(
)))
()()()
*/
