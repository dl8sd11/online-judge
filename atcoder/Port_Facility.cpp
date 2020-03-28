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
template<typename T> ostream &operator << (ostream &os,set<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1000006;
const ll MOD = 1000000007;

int n;
pair<int,int> rng[MAXN], rny[MAXN];
bool isTwo[MAXN];
vector<int> check[MAXN*2];

bool isZero () {
    vector<int> lstk = {MOD}, rstk = {MOD};
    REP (i, n) {
        while (lstk.back() < rng[i].X) {
            lstk.pop_back();
        }
        while (rstk.back() < rng[i].X) {
            rstk.pop_back();
        }
//        debug(lstk, rstk);

        if (lstk.back() > rstk.back()) {
            swap(lstk, rstk);
        }

        if (lstk.back() > rng[i].Y) {
            lstk.eb(rng[i].Y);
        } else if (rstk.back() > rng[i].Y) {
            rstk.eb(rng[i].Y);
        } else {
            return true;
        }
    }

    return false;
}

#ifdef tmd

int bf_ans = 0;
vector<int> ch;
int id[MAXN*2];
void dfs (int nd) {
    if (nd == n) {
        vector<int> lv = {MOD}, rv = {MOD};
        REP1 (i, n*2) {
            int x;
            if (id[i] > 0) {
                x = id[i] - 1;
                if (ch[x]) {
                    rv.eb(x);
                } else {
                    lv.eb(x);
                }
            } else {
                x = -id[i]-1;
                if (lv.back() == x) {
                    lv.pop_back();
                } else if (rv.back() == x) {
                    rv.pop_back();
                } else {
                    return;
                }
            }
        }

        bf_ans ++;
    } else {
        REP (i, 2) {
            ch.eb(i);
            dfs(nd+1);
            ch.pop_back();
        }
    }
}

ll bf () {
    REP (i, n) {
        id[rng[i].X] = i+1;
        id[rng[i].Y] = -i-1;
    }
    dfs(0);
    return bf_ans;
}
#endif // tmd
/*********************GoodLuck***********************/
int main () {
    IOS();
    srand(time(0));

    cin >> n;

#ifdef tmd

    vector<int> pm;
    REP1 (i, n*2) {
        pm.eb(i);
    }
    random_shuffle(ALL(pm));
    debug(pm);
#endif // tmd
    REP (i, n) {
        #ifdef tmd
 X       rng[i].X = pm[i*2];
        rng[i].Y = pm[i*2+1];
        if (rng[i].X > rng[i].Y) {
            swap(rng[i].X, rng[i].Y);
        }
        cout << rng[i].X << " " << rng[i].Y << endl;
        #else
        cin >> rng[i].X >> rng[i].Y;
        #endif // tmd

        rny[i] = rng[i];
        isTwo[i] = true;
    }

    sort(rng, rng+n);
    sort(rny, rny+n, [](pii a, pii b) {
            return a.Y < b.Y;
         });

    if (isZero()) {
        cout << 0 << endl;
        assert(bf() == 0);
        return 0;
    }

    set<int> st;
    REP (i, n) {
        auto ptr = st.lower_bound(rng[i].X);
        if (ptr != st.end() && *ptr < rng[i].Y) {
            isTwo[i] = false;
        }

        ptr = st.lower_bound(rng[i].Y);
        if (ptr != st.end()) {
            check[*ptr].eb(i);
        }

        st.insert(rng[i].Y);
    }

    st.clear();

    int cur = n-1;
    for (int i=n*2; i>=1; i--) {
        for (auto v : check[i]) {
            debug(i, v);
            debug(st);
            auto ptr = st.lower_bound(rng[v].X);
            if (ptr != st.end() && *ptr < rng[v].Y) {
                isTwo[v] = false;
            }
        }

        if (cur >= 0 && rny[cur].Y == i) {
            st.insert(rny[cur].X);
            cur--;
        }
    }

    ll ans = 1;
    REP (i, n) {
        if (isTwo[i]) {
            debug(i);
            ans = ans * 2 % MOD;
        }
    }

    cout << ans << endl;

    #ifdef tmd

    int rans = bf();
    debug(ans, rans);
    assert(ans == rans);

    #endif // tmd
}
/*
5
6 9
2 10
4 7
3 5
1 8

*/
