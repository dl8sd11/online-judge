#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LLL;
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


array<int,2> st, ed;
LLL ans;
int cnt;
bool fnd;

void dfs (LLL nd, array<int,2>  cur) {
    if (cur[0] > ed[0] || cur[1] > ed[1]) {
        return;
    }
    cnt++;
    if (cur == ed) {
        while (fnd);
        fnd = true;
        ans = nd;
    } else {
        dfs(nd*2, {cur[0], cur[0]+cur[1]});
        dfs(nd*2+1, {cur[0]+cur[1], cur[1]});
    }
}


string toString(LLL num) {
    string str;
    do {
        int digit = num % 10;
        str = to_string(digit) + str;
        num = (num - digit) / 10;
    } while (num != 0);
    return str;
}

void print (LLL x) {
    cout << toString(x) << endl;
}
/*
1
1 1 63 64
*/
/*********************GoodLuck***********************/
int main () {
    IOS();
    ll t;
    cin >> t;
    while (t--) {

        #ifdef tmdd
        st[0] = st[1] = 1;
        ed[0] = 62 + 1;
        ed[1] = 62 + 1;

        #else
        cin >> st[0] >> st[1] >> ed[0] >> ed[1];
        #endif // tmd


        fnd = false;
        cnt = 0;
        dfs(1, st);

        debug(cnt);

        if (fnd) {
            print(ans);
        } else {
            cout << -1 << endl;
        }
    }


}
