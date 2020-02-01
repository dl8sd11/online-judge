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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int n;
string s1, s2;

vector<int> pos[26];
array<int,26> id;

int bit[MAXN];

void add (int x, int val) {
    for (x++;x<MAXN;x+=-x&x) {
        bit[x] += val;
    }
}

int qry (int x) {
    int ret = 0;
    for (x++;x>0;x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    cin >> s1 >> s2;

    REP (i, SZ(s1)) {
        pos[s1[i]-'A'].emplace_back(i);
        add(i, 1);
    }

    ll sum = 0;
    for (auto c : s2) {
        add(pos[c-'A'][id[c-'A']], -1);
        sum += qry(pos[c-'A'][id[c-'A']++]);
    }

    cout << sum << endl;

}
