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

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, dp[MAXN][2];
pair<int,bool> tr[MAXN][2];
vector<int> a, v1, v2;

bool twoIncrease () {
    for (auto v : a) {
        if (v1.empty() || (v2.size() && v2.back() > v1.back())) {
            swap(v1, v2);
        }
        if (v1.empty() || v > v1.back()) {
            v1.emplace_back(v);
        } else if (v2.empty() || v > v2.back()) {
            v2.emplace_back(v);
        } else {
            return false;
        }
    }
    return true;
}

void updMax (int &tg, int val, pair<int,bool> &tra, int i, bool j) {
    if (tg < val) {
        tg = val;
        tra = {i, j};
    }
}

void updMin (int &tg, int val, pair<int,bool> &tra, int i, bool j) {
    if (tg > val) {
        tg = val;
        tra = {i, j};
    }
}

bool incAndDec () {
    dp[0][0] = 0; // Decrease
    dp[0][1] = MOD; // Increase

    REP1 (i, n-1) {
        dp[i][0] = MOD;
        dp[i][1] = 0;

        if (a[i-1] > a[i]) {
            updMin(dp[i][0], dp[i-1][0], tr[i][0], i-1, 0);
        }
        if (dp[i-1][1] > a[i]) {
            updMin(dp[i][0], a[i-1], tr[i][0], i-1, 1);
        }

        if (a[i-1] < a[i]) {
            updMax(dp[i][1], dp[i-1][1], tr[i][1], i-1, 1);
        }
        if (dp[i-1][0] < a[i]) {
            updMax(dp[i][1], a[i-1], tr[i][1], i-1, 0);
        }

        debug(dp[i-1][0]);
        debug(dp[i-1][1]);
    }

    return dp[n-1][0] < MOD || dp[n-1][1] > 0;
}

void opt () {
    if (SZ(v1) > SZ(v2)) {
        swap(v1, v2);
    }
    if (v1.empty()) {
        v1.emplace_back(v2.back());
        v2.pop_back();
    }

    cout << SZ(v1) << " " << SZ(v2) << endl;
    for (int i=0; i<SZ(v1); i++) {
        cout << v1[i] << " \n"[i==SZ(v1)-1];
    }
    for (int i=0; i<SZ(v2); i++) {
        cout << v2[i] << " \n"[i==SZ(v2)-1];
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        int d;
        cin >> d;
        a.emplace_back(d);
    }

    if (incAndDec()) {
        bool inc = dp[n-1][1] > 0;
        for (int i=n-1; i>=0; i--) {
            if (inc) {
                v1.emplace_back(a[i]);
            } else {
                v2.emplace_back(a[i]);
            }
            inc = tr[i][inc].second;
        }
        reverse(v1.begin(), v1.end());
        reverse(v2.begin(), v2.end());

        opt();
        return 0;
    }

    if (twoIncrease()) {
        opt();
        return 0;
    }

    v1.clear(), v2.clear();
    reverse(a.begin(), a.end());

    if (twoIncrease()) {
        reverse(v1.begin(), v1.end());
        reverse(v2.begin(), v2.end());

        opt();
        return 0;
    }

    cout << "Fail" << endl;



}
