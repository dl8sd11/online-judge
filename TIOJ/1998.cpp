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
const ll INF = 0x3f3f3f3f3f3f3f3f;

typedef unsigned int ui;

int n, m;
ui l[MAXN*2], r[MAXN*2],tmp, q[MAXN*3];
int pre[MAXN*7];

void add (int pos, int val) {
    pre[pos] += val;
}

void build () {
    REP1 (i, MAXN*7-1) {
        pre[i] += pre[i-1];
    }
}

int qry (int pos) {
    return pre[pos];
}

vector<ui> val;

ui high (ui b, ui len) {
    len = 32 - len;
    return b | ((1<<len)-1);
}

ui low (ui b, ui len) {
    len = 32 - len;
    return b & (~((1<<len)-1));
}
/*********************GoodLuck***********************/
int main () {

    scanf("%d%d",&n,&m);

    debug(n, m);
    REP (i, n) {
        ui sum = 0;
        int a, b, c, d;
        scanf("%d.%d.%d.%d/%d",&a,&b,&c,&d,&tmp);
        sum = a;
		sum = sum*256 + b;
		sum = sum*256 + c;
		sum = sum*256 + d;

        l[i] = low(sum, tmp);
        r[i] = high(sum, tmp);
        debug(sum, l[i], r[i]);

        val.emplace_back(l[i]);
        val.emplace_back(r[i]);
    }

    REP (i, m) {
        ui sum = 0;
        int a, b, c, d;
        scanf("%d.%d.%d.%d/%d",&a,&b,&c,&d,&tmp);
        sum = a;
		sum = sum*256 + b;
		sum = sum*256 + c;
		sum = sum*256 + d;
        q[i] = sum;
        val.emplace_back(sum);
    }

    sort(val.begin(),val.end());
    val.resize(unique(val.begin(),val.end())-val.begin());

    REP (i, n) {
        add(lower_bound(val.begin(),val.end(), l[i])-val.begin(), 1);
        add(lower_bound(val.begin(),val.end(), r[i])-val.begin()+1, -1);
    }
    build();

    REP (i, m) {
        int res = qry(lower_bound(val.begin(),val.end(), q[i])-val.begin());
        puts(res > 0 ? "TRUE" : "FALSE");
    }

}
